
CString	GetFileError(CFileException* error)
{
	if(!error)
		return "File Error Unknown";

	switch( error->m_cause )
	{

	case CFileException::none:
        return "Error Not Detected";
		break;
	case CFileException::generic:
        return "Generic Error";
		break;
	case CFileException::fileNotFound:
        return "File Not Found";
		break;
	case CFileException::badPath:
        return "Bad Path";
		break;
	case CFileException::tooManyOpenFiles:
        return "Too Many Open Files";
		break;
	case CFileException::accessDenied:
        return "Access Denied";
		break;
	case CFileException::invalidFile:
        return "Invalid File";
		break;
	case CFileException::removeCurrentDir:
        return "Cannot Remove Directory";
		break;
	case CFileException::directoryFull:
        return "Directory Full";
		break;
	case CFileException::badSeek:
        return "Error Seeking";
		break;
	case CFileException::hardIO:
        return "Hardware Error";
		break;
	case CFileException::sharingViolation:
        return "Sharing Violation";
		break;
	case CFileException::lockViolation:
        return "Lock Violation";
		break;
	case CFileException::diskFull:
        return "Disk Drive Full";
		break;
	case CFileException::endOfFile:
        return "End of File";
		break;
	}

	return "File Error Unknown";
}