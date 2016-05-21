using System.Collections.Generic;
using System.Text;

namespace Dotter.Core.Model
{
    public class GraphDescription
    {
        public string Name { get; set; }
        public GraphType Type { get; set; }
        public FlowModel FlowModel { get; set; }
        public List<GraphEdge> Edges { get; set; }

        public override string ToString()
        {
            var sb = new StringBuilder();

            if (Type == GraphType.Digraph) sb.Append("digraph ");
            if (Type == GraphType.Graph) sb.Append("graph ");
            sb.Append(Name).AppendLine("{");
            var direct = Type == GraphType.Digraph ? " -> " : " -- ";

            foreach (var edge in Edges)
            {
                sb.Append(edge.From).Append(direct).AppendLine(edge.To);
            }

            sb.AppendLine("}");
            return sb.ToString();
        }
    }
}