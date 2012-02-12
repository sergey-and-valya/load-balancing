using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Core;

namespace LoadBalancing
{
    public class LoadBalancingProblem : IProblem<int>
    {
        public LoadBalancingProblem(IMatrix<int> matrix, PartitioningParameters parameters)
        {
            Matrix = matrix;
            Parameters = parameters;
        }

        /// <summary>
        /// Параметры разбиения
        /// </summary>
        public PartitioningParameters Parameters { get; private set; }

        public IMatrix<int> Matrix { get; private set; }
        public ICriterium<int> Criterium { get { return MinMaxCriterium.Instance; } }
    }
}
