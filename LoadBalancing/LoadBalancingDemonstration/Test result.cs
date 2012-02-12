using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using AlgorithmPluginCore;
using GeneratorPluginCore;
using MatrixStorage;
using VisualizerPluginCore;
using Core;
using LoadBalancing;
using System.Diagnostics;


namespace LoadBalancingDemonstration
{
    using SolutionData = Tuple<PartitioningParameters, ISolution, double>;
    public partial class Test_result : Form
    {
        AllResults results;
    	protected class Note
			{    		 		
    			public string name;
    			public int n;
    			public int m;
				public int M1;
				public int M2;
				public double crit;
				public double diffBound;
				public double diffGood;
				public double time;
	            public Note(string _name, int _n, int _m, int _M1, int _M2, double _crit, double db, double dg, double _time, bool wd)
				{
                    name = _name;
					n=_n;
					m=_m;
					M1=_M1;
					M2=_M2;
					crit=_crit;
					diffBound=db;
					diffGood=dg;
					time=_time;
                    WithData = wd;
				}
                public bool WithData { get; set; }
    		
			}
    	protected class AgrNote
    	{
            public int count;
            public int M1;
            public int M2;
            public double crit;
            public double diffBound;
            public double time;
            public AgrNote(int _M1,int _M2, double _crit, double _diffBound, double _time)
            {
                count = 1;
                M1 = _M1;
                M2 = _M2;
                crit = _crit;
                diffBound = _diffBound;
                time = _time;
            }
            public void Add(double _crit, double _diffBound, double _time)
            {
                count++;
                crit+=_crit;
                diffBound += _diffBound;
                time+= _time;
            }
    	}
    	protected class AllResults
    	{
    		List<Note> notes;
            List<AgrNote> groupNotes;
    		public void AddElem(Note n)
    			{
    				notes.Add(n);
    			}
            public AllResults()
            {
                notes = new List<Note>();
                groupNotes = new List<AgrNote>();
            }
    		public void GetGroups(DataGridView table)
    			{
    				groupNotes = new List<AgrNote>();
    				foreach(Note n in notes)
                    {
                        bool exist=false;
                        foreach (AgrNote an in groupNotes)
    					if((n.M1==an.M1)&&(n.M2==an.M2))
                        {
    						an.Add(n.crit, n.diffBound, n.time);
                            exist = true;
                        }
                        if (!exist)
                            groupNotes.Add(new AgrNote(n.M1, n.M2, n.crit, n.diffBound, n.time));
                    }
                    foreach (AgrNote an in groupNotes)
                    {
                        an.crit /= an.count;
                        an.diffBound /= an.count;
                        an.time /= an.count;
                        table.Rows.Add(an.count, an.M1, an.M2, an.crit, an.diffBound, an.time);
                    }
    			}
            public void FillUserResults(DataGridView table, int index)
            {
                foreach (Note n in notes)
                    if ((n.M1 == groupNotes[index].M1) && (n.M2 == groupNotes[index].M2))
                        if (n.WithData)
                            table.Rows.Add(n.name, n.n, n.m, n.M1, n.M2, n.crit, n.diffBound, n.diffGood, n.time);
                        else
                            table.Rows.Add(n.name, n.n, n.m, n.M1, n.M2, n.crit, n.diffBound, '-', n.time);
            }
    			
    	}
        public Test_result(IMatrixReadStorage<int, EmptyData> storage, IMatrixReadStorage<int, SolutionData> datastorage, IAlgorithm<int, LoadBalancingProblem> algorithm, PartitioningParameters parameters)
        {
        	results = new AllResults();
            InitializeComponent();
            foreach (var matrixData in storage.ReadMatrixes())
            {
                string name = matrixData.Name;
                IMatrix<int> matrix = matrixData.Matrix;
                int n = matrixData.Matrix.Size(0);
                int m = matrixData.Matrix.Size(1);
                int M1 = parameters[0];
                int M2 = parameters[1];
                Int64 start = Stopwatch.GetTimestamp();
                ISolution solution = algorithm.Run(new LoadBalancingProblem(matrix, parameters));
                double time = (Stopwatch.GetTimestamp()-start)/(double)Stopwatch.Frequency;
                double crit = MinMaxCriterium.Instance.Value(matrix, solution);
                double w = LoadBalancing.Utilities.W(matrix, parameters);
                double diff = crit - w;
                results.AddElem(new Note(name, n, m, M1, M2, crit, diff, 0, time, false)) ;
                
            }
            foreach (var matrixData in datastorage.ReadMatrixes() )
            {
                string name = matrixData.Name;
                IMatrix<int> matrix = matrixData.Matrix;
                int n = matrixData.Matrix.Size(0);
                int m = matrixData.Matrix.Size(1);
                PartitioningParameters dataParameters = matrixData.Data.Item1;
                int M1 = dataParameters[0];
                int M2 = dataParameters[1];
                double goodCrit = matrixData.Data.Item3;
                Int64 start = Stopwatch.GetTimestamp();
                ISolution solution = algorithm.Run(new LoadBalancingProblem(matrix, dataParameters));
                double time = (Stopwatch.GetTimestamp() - start) / (double)Stopwatch.Frequency;
                double crit = MinMaxCriterium.Instance.Value(matrix, solution);
                double w = LoadBalancing.Utilities.W(matrix, dataParameters);
                double diff = crit - w;
                double goodDiff = crit - goodCrit;
                results.AddElem(new Note(name, n, m, M1, M2, crit, diff, goodDiff, time, true));

            }
            results.GetGroups(GroupedResults);
            
        }

        private void btnGrouped_Click(object sender, EventArgs e)
        {
            UserResults.Visible = false;
            GroupedResults.Visible = true;
            btnGrouped.Enabled = false;
        }

        private void CellDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex == -1)
                return;

            UserResults.Rows.Clear();
            results.FillUserResults(UserResults, e.RowIndex);
            UserResults.Visible = true;
            GroupedResults.Visible = false;
            btnGrouped.Enabled = true;
        }

    }
}
