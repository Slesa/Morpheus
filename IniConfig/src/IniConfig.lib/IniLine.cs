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

        public bool IsComment
        {
            get { return Content.Trim().StartsWith(";"); }
        }
    }
}