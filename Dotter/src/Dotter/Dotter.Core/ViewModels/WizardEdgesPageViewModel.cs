using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using Dotter.Core.Model;
using Prism.Commands;

namespace Dotter.Core.ViewModels
{
    public class WizardEdgesPageViewModel
    {
        public ObservableCollection<GraphEdge> Edges { get; set; }
        public int SelectedIndex { get; set; }

        public WizardEdgesPageViewModel()
        {
            Edges = new ObservableCollection<GraphEdge>();
        }

        public GraphDescription FillDescription(GraphDescription description)
        {
            description.Edges = new List<GraphEdge>(Edges);
            return description;
        }

        #region Add
        public DelegateCommand AddCommand
        {
            get { return new DelegateCommand(OnAdd, CanAdd); }
        }

        void OnAdd()
        {
            Edges.Add(new GraphEdge());
        }

        bool CanAdd()
        {
            if (!Edges.Any()) return true;
            var edge = Edges[Edges.Count-1];
            return !string.IsNullOrEmpty(edge.From) && !string.IsNullOrEmpty(edge.To);
        }

        #endregion

        #region Remove
        public DelegateCommand RemoveCommand
        {
            get { return new DelegateCommand(OnRemove, CanRemove).ObservesProperty(() => SelectedIndex); }
        }

        void OnRemove()
        {
            Edges.RemoveAt(SelectedIndex);
        }

        bool CanRemove()
        {
            return SelectedIndex >= 0;
        }
        #endregion
    }
}