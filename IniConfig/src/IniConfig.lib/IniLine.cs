namespace IniConfig.lib
{
    public class IniLine
    {
        public IniLine(string content)
        {
            Content = content.Trim();
        }

        public string Content { get; set; }

        public bool IsSection
        {
            get
            {
                if (!Content.StartsWith("[")) return false;
                return Content.IndexOf("]", System.StringComparison.InvariantCulture) > 1;
            }
        }

        public string Section
        {
            get
            {
                var start = Content.IndexOf('[');
                var end = Content.IndexOf(']');
                return (start>=0) && (end>start) ? Content.Substring(start+1, end-1) : string.Empty;
            }
        }

        public bool IsComment
        {
            get { return Content.Trim().StartsWith(";"); }
        }
    }
}