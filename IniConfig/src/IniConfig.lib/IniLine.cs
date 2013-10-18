using System;

namespace IniConfig.lib
{
    public class IniLine
    {
        const string TagOpenSection = "[";
        const string TagCloseSection = "]";
        const string TagComment = ";";
        const string TagPreserve = "\"";

        public IniLine(string content)
        {
            Content = content.Trim();
        }

        public string Content { get; set; }


        public bool IsEmpty
        {
            get { return string.IsNullOrWhiteSpace(Content); }
        }

        public bool IsSection
        {
            get
            {
                if (!Content.StartsWith(TagOpenSection)) return false;
                return Content.IndexOf(TagCloseSection, StringComparison.InvariantCulture) > 1;
            }
        }

        public string Section
        {
            get
            {
                var start = Content.IndexOf(TagOpenSection, StringComparison.InvariantCulture);
                var end = Content.IndexOf(TagCloseSection, StringComparison.InvariantCulture);
                return (start>=0) && (end>start) ? Content.Substring(start+1, end-1) : string.Empty;
            }
        }

        public bool IsComment
        {
            get { return Content.Trim().StartsWith(TagComment); }
        }

        public string Comment
        {
            get
            {
                var start = Content.IndexOf(TagComment, StringComparison.InvariantCulture);
                return (start >= 0) ? Content.Substring(start + 1).Trim() : string.Empty;
            }
        }

        public string Entry
        {
            get
            {
                var entry = GetEntry();
                CheckEntryOrValue(entry);
                return entry;
            }
        }

        public string Value
        {
            get
            {
                CheckEntryOrValue(Content.TrimStart());
                var value = GetValue();
                if (value.StartsWith(TagPreserve) && value.EndsWith(TagPreserve))
                    value = value.Substring(1, value.Length - 2);
                return value;
            }
        }

        void CheckEntryOrValue(string entry)
        {
            if (entry.StartsWith(TagComment) || entry.StartsWith(TagOpenSection) || entry.StartsWith(TagCloseSection))
                throw new InvalidOperationException(string.Format("'{0}': entry has invalid format", Content));
        }

        string GetEntry()
        {
            var index = Content.IndexOf('=');
            return index > 0 ? Content.Substring(0, index).Trim() : string.Empty;
        }

        string GetValue()
        {
            var index = Content.IndexOf('=');
            return index > 0 ? Content.Substring(index+1).Trim() : string.Empty;
        }

    }
}