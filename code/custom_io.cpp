#include "custom_io.h"
#if defined(ADVENTUREGAME_WIN32)
#include <Windows.h> // get Win32 API stuff
#elif defined(ADVENTUREGAME_LINUX)
#include "unistd.h" // write( )
#endif
#include <sstream>
using namespace std;
using namespace adventure_game;

#if defined(ADVENTUREGAME_LINUX) || defined(ADVENTUREGAME_WIN32)

our_ostream_buffer::our_ostream_buffer()
{
    // open resource for writing to the standard output
    // note: don't have to close these since they're standard
#ifdef ADVENTUREGAME_LINUX
    _fdOutput = 0; // assign stdout descriptor
#else
    _hOutput = ::GetStdHandle(STD_OUTPUT_HANDLE); // get stdout handle
    // cache console specifications for
    // later use
    CONSOLE_SCREEN_BUFFER_INFO info;
    if ( ::GetConsoleScreenBufferInfo(_hOutput,&info) )
    {
	_wAttributesOriginal = info.wAttributes;
	_colCnt = info.dwSize.X;
	_rowCnt = info.dwSize.Y;
    }
    else
    {
	_wAttributesOriginal = 0;
	_colCnt = 0;
	_rowCnt = 0;
    }
#endif
    _attrib = consolea_normal;
    _trigger = false;
}
streambuf::int_type our_ostream_buffer::overflow(int_type ch)
{
#ifdef ADVENTUREGAME_LINUX
    if (ch >= 0 && write(_fdOutput,&ch,1)==1)
	return ch;
#else
    DWORD charsWrote;
    if (ch >= 0 && ::WriteFile(_hOutput,&ch,1,&charsWrote,NULL) && charsWrote==1)
	return ch;
#endif
    return -1;
}
streamsize our_ostream_buffer::xsputn(const char* data,streamsize n)
{
    // write a buffer
#ifdef ADVENTUREGAME_LINUX
    if (_trigger) // handle color
    {
	string s = "\033[1;";
	stringstream ss;
	ss << int(_attrib);
	s += ss.str();
	s.push_back('m');
	_trigger = false;
	write(_fdOutput,s.c_str(),s.length());
    }
    return write(_fdOutput,data,n);
#else
    DWORD bytesOut;
    if (_trigger) // handle color
    {
	if (_attrib == consolea_normal)
	    _attrib = (console_attribute) _wAttributesOriginal;
	::SetConsoleTextAttribute(_hOutput,_attrib);
	_trigger = false;
    }
    ::WriteFile(_hOutput,data,n,&bytesOut,NULL);
    return streamsize(bytesOut);
#endif
}

our_ostream::our_ostream(our_ostream_buffer& buffer)
    : ostream(&buffer)
{
    _pBuf = &buffer;
}
void our_ostream::clear_screen()
{
#ifdef ADVENTUREGAME_WIN32
    CHAR_INFO* clearBuffer;
    COORD sz, origin;
    SMALL_RECT writeRect;
    int bufSz = _pBuf->_colCnt*_pBuf->_rowCnt;
    try {
	clearBuffer = new CHAR_INFO[bufSz];
    }
    catch (std::bad_alloc)
    {
	return;
    }
    origin.X = 0;
    origin.Y = 0;
    sz.X = _pBuf->_colCnt;
    sz.Y = _pBuf->_rowCnt;
    writeRect.Left = 0;
    writeRect.Top = 0;
    writeRect.Right = _pBuf->_colCnt-1;
    writeRect.Bottom = _pBuf->_rowCnt-1;
    for (int i = 0;i<bufSz;i++)
    {
	clearBuffer[i].Attributes = _pBuf->_wAttributesOriginal;
	clearBuffer[i].Char.AsciiChar = ' ';
    }
    ::WriteConsoleOutput(_pBuf->_hOutput,clearBuffer,sz,origin,&writeRect);
    delete[] clearBuffer;
#else
    *this << "\033[2J";
#endif
}
void our_ostream::set_attribute(console_attribute a)
{
    if (_pBuf->_attrib != a)
    {
	_pBuf->_attrib = a;
	_pBuf->_trigger = true;
    }
}

static our_ostream_buffer theOutputStreamBuffer;
our_ostream adventure_game::exCout(theOutputStreamBuffer);

#else
// share stream buffers with 'cout'
our_ostream adventure_game::exCout( cout.rdbuf() );

#endif

our_ostream& adventure_game::operator <<(our_ostream& stream,console_attribute a)
{
    stream.set_attribute(a);
    return stream;
}
