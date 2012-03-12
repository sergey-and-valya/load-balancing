using System.Collections.Generic;
using Core;

namespace CoreParallel
{
    /// <summary>
    /// Последовательное преобразование решения
    /// </summary>
    public class CombineModifications : ISolutionModification
    {
        /// <summary>
        /// Последовательное преобразование решения
        /// </summary>
        /// <param name="modifications">Набор последовательных преобразований решения</param>
        public CombineModifications(IEnumerable<ISolutionModification> modifications)
        {
            Modifications = modifications;
        }

        /// <summary>
        /// Последовательное преобразование решения
        /// </summary>
        /// <param name="modifications">Набор последовательных преобразований решения</param>
        public CombineModifications(params ISolutionModification[] modifications) :
            this(modifications as IEnumerable<ISolutionModification>)
        {
        }

        public ISolution ApplyTo(ISolution solution)
        {
            ISolution currentSolution = solution;

            foreach (var modification in Modifications)
            {
                currentSolution = modification.ApplyTo(currentSolution);
            }

            return currentSolution;
        }

        protected readonly IEnumerable<ISolutionModification> Modifications;
    }
}
