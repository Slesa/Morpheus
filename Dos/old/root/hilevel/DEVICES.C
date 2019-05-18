 #include       <HILEVEL/DEVICES.H>
 #include       <LOLEVEL/PORTSER.H>
 #include       <LOLEVEL/PORTPAR.H>
 #include       <BASICS/DISK.H>
 #include       <BASICS/MEMALLOC.H>
 #include       <DEFS/ERRORDEF.H>

 #define        __FUNC__     ERR_DEV_INIT
 VOID  CDECL    DevInit      ( dev )
 SDev*          dev;
 {
  Assert( dev!=NULL, ERR_PTR );
  switch( dev->iType )
  {
   case DEV_NUL:
        break;
   case DEV_SER:
        SerSetPort( dev->iSubNum, dev->d.ser.wAdr );
        SerInit( dev->iSubNum, dev->d.ser.lBaud, dev->d.ser.bData, dev->d.ser.cPari, dev->d.ser.bStop );
        if( dev->d.ser.iIrq!=-1 )
         SerSetHandler( dev->iSubNum );
        break;
   case DEV_PAR:
        ParSetPort( dev->iSubNum, dev->d.par.wAdr );
        break;
   case DEV_IMC:
   case DEV_FILE:
        break;
   default:
        SystemError( __FILE__, __FUNC__, __LINE__, ERR_COUNT );
  }
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_DEV_DONE
 VOID  CDECL    DevDone      ( dev )
 SDev*          dev;
 {
  Assert( dev!=NULL, ERR_PTR );
  switch( dev->iType )
  {
   case DEV_NUL:
        break;
   case DEV_SER:
        if( dev->d.ser.iIrq!=-1 )
         SerClrHandler( dev->iSubNum );
        SerDone( dev->iSubNum );
        break;
   case DEV_PAR:
        break;
   case DEV_IMC:
   case DEV_FILE:
        break;
   default:
        SystemError( __FILE__, __FUNC__, __LINE__, ERR_COUNT );
  }
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_DEV_LOAD
 VOID  CDECL    DevLoad       ( dev, pcFile )
 SDev*          dev;
 CHAR*          pcFile;
 {
  SFile*        fh           = DskFileOpen( pcFile, "rb" );
  Assert( dev!=NULL, ERR_PTR );
  Assert( fh!=NULL, ERR_DISK_OPEN );
  Assert( DskFileRead( dev, sizeof( SDev ), 1, fh ), ERR_DISK_READ );
  DskFileClose( fh );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_DEV_SAVE
 VOID  CDECL    DevSave       ( dev, pcFile )
 SDev*          dev;
 CHAR*          pcFile;
 {
  SFile*        fh           = DskFileOpen( pcFile, "w+b" );
  Assert( dev!=NULL, ERR_PTR );
  Assert( fh!=NULL, ERR_DISK_OPEN );
  Assert( DskFileWrite( dev, sizeof( SDev ), 1, fh ), ERR_DISK_WRITE );
  DskFileClose( fh );
 }
 #undef         __FUNC__
