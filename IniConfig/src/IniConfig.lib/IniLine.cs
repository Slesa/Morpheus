using System;

namespace IniConfig.lib
{
    /// <summary>
    /// An instance represents one single line within a configuration file.
    /// </summary>
    public class IniLine
    {
        const string TagOpenSection = "[";
        const string TagCloseSection = "]";
        const string TagComment = ";";
        const string TagPreserve = "\"";

        /// <summary>
        /// Create an instance of an empty line.
        /// </summary>
        public IniLine()
        {
            Content = string.Empty;
        }

        /// <summary>
        /// Create an instance of a line containing content .
        /// </summary>
        /// <param name="content">The content of the line</param>
        public IniLine(string content)
        {
            Content = content.Trim();
        }

        /// <summary>
        /// The content of the configuration line.
        /// </summary>
        public string Content { get; set; }

        /// <summary>
        /// True, if the line contains only whitespaces.
        /// </summary>
        public bool IsEmpty
        {
            get { return string.IsNullOrWhiteSpace(Content); }
        }

        /// <summary>
        /// True, if the configuration line contains a section definition.
        /// </summary>
        public bool IsSection
        {
            get
            {
                if (!Content.StartsWith(TagOpenSection)) return false;
                return Content.IndexOf(TagCloseSection, StringComparison.InvariantCulture) > 1;
            }
        }

        /// <summary>
        /// If the line consist of a section definition, the name of the section. An empty string otherwise.
        /// </summary>
        public string Section
        {
            get
            {
                var start = Content.IndexOf(TagOpenSection, StringComparison.InvariantCulture);
                var end = Content.IndexOf(TagCloseSection, StringComparison.InvariantCulture);
                return (start>=0) && (end>start) ? Content.Substring(start+1, end-1) : string.Empty;
            }
            set { Content = TagOpenSection + value + TagCloseSection; }
        }

        /// <summary>
        /// True, if the line contains a comment
        /// </summary>
        public bool IsComment
        {
            get { return Content.Trim().StartsWith(TagComment); }
        }

        /// <summary>
        /// If the line consists of a comment, the text of the comment. An empty string otherwise.
        /// </summary>
        public string Comment
        {
            get
            {
                var start = Content.IndexOf(TagComment, StringComparison.InvariantCulture);
                return (start >= 0) ? Content.Substring(start + 1).Trim() : string.Empty;
            }
            set { Content = TagComment + " " + value; }
        }

        public bool IsEntry
        {
            get
            {
                var entry = Content.TrimStart();
                if (entry.StartsWith(TagComment) || entry.StartsWith(TagOpenSection) || entry.StartsWith(TagCloseSection))
                    return false;
                return !string.IsNullOrEmpty(GetEntry());
            }
        }

        /// <summary>
        /// The entry of the configuration line, if the line consists of an attribute/value pair.
        /// InvalidOperationException can be thrown, if the line is a section or a comment.
        /// </summary>
        public string Entry
        {
            get
            {
                CheckInvalidOperation();
                var entry = GetEntry();
                return entry;
            }
            set { Content = value + " = " + GetValue(); }
        }

        /// <summary>
        /// The value of the configuration line, if the line consists of an attribute/value pair.
        /// InvalidOperationException can be thrown, if the line is a section or a comment.
        /// </summary>
        public string Value
        {
            get
            {
                CheckInvalidOperation();
                var value = GetValue();
                return value;
            }
            set
            {
                //if (value.StartsWith(TagPreserve) && value.EndsWith(TagPreserve))
                Content = GetEntry() + " = " + value;
            }
        }

        void CheckInvalidOperation()
        {
            var entry = Content.TrimStart();
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
            if( index < 0 ) return string.Empty;
            var value = Content.Substring(index + 1).Trim();
            if (value.StartsWith(TagPreserve) && value.EndsWith(TagPreserve))
                value = value.Substring(1, value.Length - 2);
            return value;
        }
    }
}