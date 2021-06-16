#pragma once

//#include <stdio.h>

#include <cstdio>
#include <ctime>
#include <string>
//#include <format>

class debuglog
{
private:
	std::FILE*	m_logfile;
	std::time_t	m_start;

public:
	debuglog() { m_logfile = nullptr;	m_start = 0; }
	~debuglog() { if (m_logfile) fclose(m_logfile); }

	bool enablelog(std::string logpath)
	{
		if (m_logfile)
		{
			fclose(m_logfile);
			m_logfile = nullptr;
		}

		m_start = std::clock();
#ifdef WIN32	
		fopen_s(&m_logfile, logpath.c_str(), "w");
#else
		m_logfile = fopen(logpath, "w");
#endif
		if (m_logfile)
			return true;

		return false;
	}

	void disablelog()
	{
		if (m_logfile)
		{
			fclose(m_logfile);
			m_logfile = nullptr;
		}
	}

	bool isactive()
	{
		return (m_logfile != nullptr);
	}

	void writeentrytolog(std::string entry)
	{
		if (m_logfile)
		{
			char temptext[128];
			float functiontime = (float)(std::clock() - m_start) / 1000.f;

			sprintf_s(temptext, 128, "%f %s\n", functiontime, entry.c_str());

			fprintf(m_logfile, temptext);
			fflush(m_logfile);
		}
	}
};

