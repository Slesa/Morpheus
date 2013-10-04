
    class			TInifile
    {
    protected:
        class		TLine;
        typedef		QList<TLine>			TLineList;
        typedef		QListIterator<TLine>	TLineIt;
    public:
        class		TSection;
        typedef		QDict<TSection>			TSectionList;
        typedef		QDictIterator<TSection>	TSectionIt;
        class		TEntry;
        typedef		QList<TEntry>			TEntryList;
        typedef		QListIterator<TEntry>	TEntryIt;

    public:
        static bool		isSection(const QString& line);
        static bool		isComment(const QString& line);
        static bool		isEntry(const QString& line);
        static bool		isEmpty(const QString& line);
        static bool		isInclude(const QString& line);
        static QString	getSection(const QString& line);
        static QString	setSection(const QString& section);
        static QString	getComment(const QString& line);
        static QString	setComment(const QString& comment);
        static QString	getEntry(const QString& line);
        static void		setEntry(QString& line, const QString& entry);
        static QString	getValue(const QString& line);
        static void		setValue(QString& line, const QString& value);
        static void		setEntry(QString& line, const QString& entry, const QString& value);
        static QString	getInclude(const QString& line);
        static QString	setInclude(const QString& include);

    protected:
        class		TLine
        {
        public: // Member access
            bool	mustSave() const
            {
                return m_mustSave;
            }
            QString		getLine() const
            {
                return m_Line;
            }
            void	setLine(const QString& line)
            {
                m_Line = line;
            }
        public:
            bool	isSection()
            {
                return TInifile::isSection(m_Line);
            }
            bool	isComment()
            {
                return TInifile::isComment(m_Line);
            }
            bool	isEntry()
            {
                return TInifile::isEntry(m_Line);
            }
            bool	isEmpty()
            {
                return TInifile::isEmpty(m_Line);
            }
            bool	isInclude()
            {
                return TInifile::isInclude(m_Line);
            }
            QString	getSection()
            {
                return TInifile::getSection(m_Line);
            }
            void	setSection(const QString& section)
            {
                m_Line = TInifile::setSection(section);
            }
            QString	getEntry()
            {
                return TInifile::getEntry(m_Line);
            }
            void	setEntry(const QString& entry)
            {
                TInifile::setEntry(m_Line, entry);
            }
            QString	getValue()
            {
                return TInifile::getValue(m_Line);
            }
            void	setValue(const QString& value)
            {
                TInifile::setValue(m_Line, value);
            }
            void	setValue(const TVariant& value)
            {
                TInifile::setValue(m_Line, value);
            }
            void 	setEntry(const QString& entry, const QString& value)
            {
                TInifile::setEntry(m_Line, entry, value);
            }
            void	setEntry(const QString& entry, const TVariant& value)
            {
                TInifile::setEntry(m_Line, entry, value);
            }
            QString	getInclude()
            {
                return TInifile::getInclude(m_Line);
            }
            void	setInclude(const QString& include)
            {
                m_Line = TInifile::setInclude(include);
            }
        protected:
            QString	m_Line;
            bool	m_mustSave;
        };

    public:
        class			TEntry
        {
        public:
            TEntry(TLine* line)
            : m_Line(line)
            , m_AutoDelete(false)
            {
                m_Value = m_Line->getValue();
            }
            TEntry()
            : m_AutoDelete(true)
            {
                m_Line = new TLine();
            }
            ~TEntry()
            {
                if( m_AutoDelete )
                    delete m_Line;
            }
            QString	getEntry()
            {
                return m_Line->getEntry();
            }
            void	setEntry(const QString& name)
            {
                m_Line->setEntry(name);
            }
            QString	getValue()
            {
                return m_Line->getValue();
            }
            void	setValue(const QString& name)
            {
                m_Value = name;
                m_Line->setValue(m_Value);
            }
            void	setEntry(const QString& entry, const QString& value)
            {
                m_Value = value;
                m_Line->setEntry(entry, value);
            }
            operator	TVariant& ()
            {
                return m_Value;
            }
            TEntry&	operator = (const TVariant& value)
            {
                m_Value = value;
                m_Line->setValue(m_Value);
                return *this;
            }
            bool	isComment()
            {
                return m_Line->isComment();
            }
        protected:
            TLine*	getLine()
            {
                return m_Line;
            }
        protected:
            TLine*	m_Line;
            TVariant	m_Value;
            bool	m_AutoDelete;
            friend class TSection;
        };

    public: // Inner class TGroup
        class		TSection
        {
        public:
            TSection(TLineList& lines, TLine* line)
            : m_Lines(lines)
            , m_Line(line)
            , m_CurrEntry(m_Entries)
            {
                m_Entries.setAutoDelete(TRUE);
            }
            QString	getName()
            {
                return m_Line->getSection();
            }
            void	setName(const QString& name)
            {
                m_Line->setSection(name);
            }
        public:
//			TEntry*	findEntry(const QString& str, bool match=false)
            TEntry*	findEntry(const QString& str)
            {
                QString cmp1 = str.lower();
                cmp1.stripWhiteSpace();
                TEntryIt it(m_Entries);
                TEntry* entry;
                for( entry=it.toFirst(); entry; entry=++it)
                {
                    QString cmp2 = entry->getEntry().lower();
                    if( cmp1==cmp2 )
                        return entry;
                }
                return NULL;
            }
//			TEntry*	firstEntry(const QString& str=QString::null, bool match=false)
            TEntry*	firstEntry(bool comments=false)
            {
                TEntry*	entry= m_CurrEntry.toFirst();
                if( !entry )
                    return NULL;
                if( comments || !entry->isComment() )
                    return entry;
                return nextEntry();
            }
            TEntry*	nextEntry(bool comments=false)
            {
                if( comments )
                    return ++m_CurrEntry;
                TEntry*	entry;
                do
                {
                    entry = ++m_CurrEntry;
                    if( !entry )
                        break;
                } while( entry->isComment() );
                return entry;
            }
            TEntry*	addEntry(const QString& name, const TVariant& value)
            {
                QString entname;
                TInifile::setEntry(entname, name);
                int pos = m_Lines.find(m_Line);
                Assert(pos!=-1, errCount, errIniAddentry);
                TLine* line = new TLine(entname);
                InifileAssert(line, errMemory, errIniAddentry);
                m_Lines.insert(pos+1,line);
                TEntry* entry = new TEntry(line);
                InifileAssert(entry, errMemory, errIniAddentry);
                *entry = value;
                m_Entries.append(entry);
                return entry;
            }
            TEntry*	addEntry(const QString& name, const QString& value)
            {
                QString entname;
                TInifile::setEntry(entname, name, value);
                int pos = m_Lines.find(m_Line);
                Assert(pos!=-1, errCount, errIniAddentry);
                TLine* line = new TLine(entname);
                InifileAssert(line, errMemory, errIniAddentry);
                m_Lines.insert(pos+1,line);
                TEntry* entry = new TEntry(line);
                InifileAssert(entry, errMemory, errIniAddentry);
                m_Entries.append(entry);
                return entry;
            }
            bool	renEntry(const QString& newname, const QString& oldname)
            {
                TEntry* entry = findEntry(oldname);
                if( !entry )
                    return false;
                entry->setEntry(newname);
                return true;
            }
            bool	delEntry(const QString& name)
            {
                TEntry* entry = findEntry(name);
                if( !entry )
                    return false;
                TLine* line = entry->getLine();
                InifileAssert(m_Entries.remove(entry), errParameter, errIniDelentry);
//				delete entry;
                InifileAssert(m_Lines.remove(line), errParameter, errIniDelentry);
//				delete line;
                return true;
            }
            void	clear()
            {
                TEntryIt it(m_Entries);
                for(TEntry* entry=it.toFirst(); entry; entry=++it)
                {
                    TLine* line = entry->getLine();
                    InifileAssert(m_Lines.remove(line), errParameter, errIniClearsection);
                    m_Entries.remove(entry);
//					delete entry;
                }
                m_Entries.clear();
            }
            void		setValue(const TVariant& value, const QString& _entry)
            {
                TEntry* entry = findEntry(_entry);
                if( !entry )
                    addEntry(_entry, value);
                else
                    *entry = value;
            }
            void		setValue(const QString& value, const QString& _entry)
            {
                TEntry* entry = findEntry(_entry);
                if( !entry )
                    addEntry(_entry, value);
                else
                    *entry = value;
            }
            bool		getValue(TVariant& value, const QString& _entry)
            {
                TEntry* entry = findEntry(_entry);
                if( !entry )
                    return false;
                value = *entry;
                return true;
            }
            void		push()
            {
                m_Stack.push(new TEntryIt(m_CurrEntry));
            }
            void		pop()
            {
                TEntryIt* it = m_Stack.pop();
                if(!it)
                    return;
                m_CurrEntry = *it;
                delete it;
            }
        protected:
            TLine*	getLine()
            {
                return m_Line;
            }
            void	addEntry(TLine* line)
            {
                InifileAssert(line, errParameter, errIniAddentry);
                TEntry* entry = new TEntry(line);
                InifileAssert(entry, errMemory, errIniAddentry);
                m_Entries.append(entry);
            }
        protected:
            TLineList&	m_Lines;
            TLine*		m_Line;
            TEntryList	m_Entries;
            TEntryIt	m_CurrEntry;
            QStack<TEntryIt>	m_Stack;
            friend class TInifile;
        };

    public: // Group access functions
        TSection*	findSection(const QString& str)
        {
//debug("Searching %s", (const char*) str);
            TSection* sect = m_Sects.find(str);
//debug("found %p", group);
            return sect;
        }
//		TGroup*		firstGroup(const QString& str=QString::null, bool match=false)
        TSection*	firstSection()
        {
            return m_CurrSect.toFirst();
        }
        TSection*	nextSection()
        {
            return ++m_CurrSect;
        }
        TSection*	addSection(const QString& name)
        {
            TSection* sect = findSection(name);
            if( sect )
                return sect;
            QString section = setSection(name);
            TLine* line = new TLine(section);
            InifileAssert(line, errMemory, errIniAddsection);
            m_Lines.append(line);
            sect = new TSection(m_Lines, line);
            InifileAssert(sect, errMemory, errIniAddsection);
            m_Sects.insert(name, sect);
            return sect;
        }
        bool		renSection(const QString& newname, const QString& oldname)
        {
            TSection* sect = findSection(oldname);
            if( !sect )
                return false;
            sect->setName(newname);
            return true;
        }
        bool		delSection(const QString& name);

    public:
        void		clrValue(const QString& _group, const QString& _entry)
        {
            TSection* sect = findSection(_group);
            if( !sect )
                return;
            InifileAssert(sect, errPointer, errIniClrvalue);
            sect->delEntry(_entry);
        }
        void		setValue(const TVariant& value, const QString& _group, const QString& _entry)
        {
            TSection* sect = findSection(_group);
            if( !sect )
                sect = addSection(_group);
            InifileAssert(sect, errPointer, errIniSetvalue);
            TEntry* entry = sect->findEntry(_entry);
            if( !entry )
                sect->addEntry(_entry, value);
            else
                *entry = value;
        }
        void		setString(const QString& value, const QString& _group, const QString& _entry)
        {
            TSection* sect = findSection(_group);
            if( !sect )
                sect = addSection(_group);
            InifileAssert(sect, errPointer, errIniSetvalue);
            TEntry* entry = sect->findEntry(_entry);
            if( !entry )
                sect->addEntry(_entry, value);
            else
                *entry = value;
        }
        TVariant	getValue(const QString& _group, const QString& _entry, const TVariant& def=TVariant())
        {
            TVariant value(def);
            TSection* sect = findSection(_group);
            if( !sect )
                return value;
            TEntry* entry = sect->findEntry(_entry);
            if( !entry )
                return value;
            value = *entry;
            return value;
        }
        QString		getString(const QString& _group, const QString& _entry, const QString& def=QString::null)
        {
            QString value = def;
            TSection* sect = findSection(_group);
            if( !sect )
                return value;
            TEntry* entry = sect->findEntry(_entry);
            if( !entry )
                return value;
            value = entry->getValue();
            return value;
        }
    protected:
        TSectionList	m_Sects;
        TSectionIt	m_CurrSect;
        TLineList	m_Lines;

    public:
        void		clear();
        void		load(const QString& file)
        {
            clear();
            append(file, true);
        }
        void		append(const QString& file, bool orig);
        void		append(TInifile& file, bool orig);
        void		save(const QString& file=QString::null);
        QString		getFilename() const
        {
            return m_Filename;
        }


    protected:
        QString		m_Filename;

    private:
        TInifile(const TInifile&);
        TInifile& operator = (const TInifile&);
    };


 * 
 * 
namespace Basics
{
    TInifile::TInifile(bool nouni)
    : m_Sects(17, false)
    , m_CurrSect(m_Sects)
    {
        m_Sects.setAutoDelete(TRUE);
        m_Lines.setAutoDelete(TRUE);
    }

    TInifile::TInifile(const QString& file, bool nouni)
    : m_Sects(17, false)
    , m_CurrSect(m_Sects)
    {
        m_Sects.setAutoDelete(TRUE);
        m_Lines.setAutoDelete(TRUE);
        load(file);
    }

    TInifile::TInifile(const char* file, bool nouni)
    : m_Sects(17, false)
    , m_CurrSect(m_Sects)
    {
        m_Sects.setAutoDelete(TRUE);
        m_Lines.setAutoDelete(TRUE);
        load(file);
    }

    void TInifile::save(const QString& file)
    {
        QString cp = (file==QString::null) ? m_Filename : file;
        InifileAssert(!cp.isEmpty(), errParameter, errIniSave);

        TFile fh(cp);
        fh.open(IO_WriteOnly);

        QTextStream st(&fh);
//		st.setCodec(QTextCodec::codecForName("utf8"));

        TLineIt it(m_Lines);
        for( TLine* line=it.toFirst(); line; line=++it )
        {
            if( line->mustSave() )
            {
                st << line->getLine() << "\r\n";
            }
        }
    }

    void TInifile::append(const QString& file, bool save/*=false*/)
    {
        InifileAssert(file!=QString::null, errParameter, errIniAppend);
        m_Filename = file;

        if( !QFile::exists(file) )
            return;
        TFile fh(file);
        fh.open(IO_ReadOnly);
        QTextStream st(&fh);

        QString tmp;
        TSection* sect = NULL;

//		while( !st.atEnd() )
        for( ;; )
        {
            tmp = st.readLine();
            if( tmp.isEmpty() && st.atEnd() )
                break;
            TLine* line = new TLine(tmp,save);
            InifileAssert(line!=NULL, errMemory, errIniAppend);

            m_Lines.append(line);
            if( line->isInclude() )
            {
                append(line->getInclude(), false);
                continue;
            }
            if( line->isSection() )
            {
                sect = m_Sects.find(line->getSection());
                if( sect )
                    continue;
                sect = new TSection(m_Lines, line);
                InifileAssert(sect!=NULL, errMemory, errIniAppend);
                m_Sects.insert(sect->getName(), sect);
                continue;
            }
            if( line->isEntry() || line->isComment() )
            {
                if( !sect )
                    continue;
//				TEntry* entry = sect->findEntry(line->getEntry());
//				if( !entry )
                    sect->addEntry(line);
//				else
//					entry->setValue(line->getValue());
            }
        }
    }

    void TInifile::append(TInifile& file, bool save/*=false*/)
    {
        TLineIt it(file.m_Lines);
        for( TLine* line=it.toFirst(); line; line=++it )
        {
            TLine* l = new TLine(line->getLine(), save);
            InifileAssert(l!=NULL, errMemory, errIniAppend);
            m_Lines.append(l);
        }
    }

    bool TInifile::isSection(const QString& line)
    {
        int len = line.length();
        for( int i=0; i<len; i++ )
        {
            if( line[i]=='[' )
            {
                if( line.find(']', i+1)==-1 )
                    return false;
                return true;
            }
            if( line[i]!=' ' || line[i]!='\t' )
                break;
        }
        return false;
    }

    bool TInifile::isComment(const QString& line)
    {
        int len = strlen(line);
        for( int i=0; i<len; i++ )
        {
            if( line[i]==';' )
                return true;
            if( line[i]!=' ' || line[i]!='\t' )
                break;
        }
        return false;
    }

    bool TInifile::isEntry(const QString& line)
    {
        int len = line.length();
        for( int i=0; i<len; i++ )
        {
            if( line[i]==';' || line[i]=='[' || line[i]=='<' )
                return false;
            if( line[i]!=' ' && line[i]!='\t' )
                break;
        }
        return true;
    }

    bool TInifile::isEmpty(const QString& line)
    {
        int len = line.length();
        if( len==0 )
            return true;
        for( int i=0; i<len; i++ )
        {
            if( line[i]!=' ' || line[i]!='\t' )
                return false;
        }
        return true;
    }

    bool TInifile::isInclude(const QString& line)
    {
        int len = line.length();
        for( int i=0; i<len; i++ )
        {
            if( line[i]=='#' )
            {
                if( line.find('<', i+1)!=-1 && line.findRev('>')!=-1 )
                    return true;
            }
            if( line[i]==';' || line[i]=='[' )
                break;
            if( line[i]!=' ' || line[i]!='\t' )
                break;
        }
        return false;
    }

    QString TInifile::getInclude(const QString& line)
    {
        int left = line.find('<');
        InifileAssert(left>=0, errSyntax, errIniGetinclude)
        int right = line.find('>', left);
        InifileAssert(right>=0, errSyntax, errIniGetinclude)
        return line.mid(left+1, right-1);
    }

    QString TInifile::getComment(const QString& line)
    {
        if( line.isEmpty() )
            return QString();
        if( line[0]!=';' && line[0]!='#' )
            return QString();
        return line.right(1);
    }

    QString TInifile::setComment(const QString& comment)
    {
        if( comment.isEmpty() )
            return QString(";");
        if( comment[0]==';' || comment[0]=='#')
            return comment;
        QString str = "; ";
        return str + comment;
    }

    QString TInifile::getSection(const QString& line)
    {
        int left = line.find('[');
        InifileAssert(left>=0, errSyntax, errIniGetsection);
        int right = line.find(']', left);
        InifileAssert(right>=0, errSyntax, errIniGetsection);
        QString ret = line.mid(left+1, right-1);
        return ret;
    }

    QString	TInifile::setSection(const QString& section)
    {
        QString str;
        str = "[" + section + "]";
        return str;
    }

    QString TInifile::getEntry(const QString& line)
    {
        int pos = line.find('=');
        if( pos<0 )
            return QString();
        QString ret = line.left(pos).stripWhiteSpace();
        return ret;
    }

    void TInifile::setEntry(QString& line, const QString& entry)
    {
        int pos = line.find('=');
        if( pos<0 )
        {
            line = entry + '=';
            return;
        }
        QString right = line.right(line.length()-pos);
        line = entry + right.stripWhiteSpace();
    }

    QString TInifile::getValue(const QString& line)
    {
        int pos = line.find('=');
        if( pos<0 )
            return QString();
        QString ret = line.right(line.length()-pos-1);
        return ret.stripWhiteSpace();
    }

    void TInifile::setEntry(QString& line, const QString& entry, const QString& value)
    {
        line = entry.stripWhiteSpace() + " = " + value.stripWhiteSpace();
    }

    void TInifile::setValue(QString& line, const QString& value)
    {
        int pos = line.find('=');
        if( pos<0 )
        {
            if( line.isEmpty() )
                line = "default = " + value.stripWhiteSpace();
            else
            {
                line += " = ";
                line += value.stripWhiteSpace();
            }
            return;
        }
        QString left = line.left(pos);
        line = left.stripWhiteSpace() + " = " + value.stripWhiteSpace();
    }

    QString TInifile::setInclude(const QString& include)
    {
        QString str;
        str = "<" + include + ">";
        return str;
    }

    bool TInifile::delSection(const QString& name)
    {
        TSection* sect = findSection(name);
        if( !sect )
            return false;
//		for(TEntry* entry=sect->firstEntry(TRUE); entry; entry=sect->nextEntry(TRUE))
//			sect->delEntry(entry->getEntry());
        while(TEntry* entry=sect->firstEntry(TRUE))
            sect->delEntry(entry->getEntry());
        sect->clear();
        TLine* line = sect->getLine();
        InifileAssert(m_Sects.remove(sect->getName()), errParameter, errIniDelsection);
//			delete sect;
        InifileAssert(m_Lines.remove(line), errParameter, errIniDelsection);
//			delete line;
        return true;
    }
} 
#endif

