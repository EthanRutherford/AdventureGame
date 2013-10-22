/* custom_io.cpp
 * Project: AdventureGame
 * Owner: Roger Gee
 */
#include "custom_io.h"
#if defined(ADVENTUREGAME_WIN32)
#include <Windows.h> // get Win32 API stuff
#elif defined(ADVENTUREGAME_LINUX)
#include "unistd.h" // write( )
#endif
#include <sstream>
using namespace std;
using namespace adventure_game;

// console_attributes
console_attribute::console_attribute(unsigned short initial)
{
    value = initial;
}
console_attribute& console_attribute::operator =(unsigned short us)
{
    value = us;
    return *this;
}
bool adventure_game::operator ==(console_attribute left,console_attribute right)
{
    return left.value == right.value;
}
bool adventure_game::operator !=(console_attribute left,console_attribute right)
{
    return left.value != right.value;
}
#ifdef ADVENTUREGAME_LINUX
const console_attribute adventure_game::consolea_normal(0);
const console_attribute adventure_game::consolea_fore_black(30);
const console_attribute adventure_game::consolea_fore_red(31);
const console_attribute adventure_game::consolea_fore_green(32);
const console_attribute adventure_game::consolea_fore_yellow(33);
const console_attribute adventure_game::consolea_fore_blue(34);
const console_attribute adventure_game::consolea_fore_magenta(35);
const console_attribute adventure_game::consolea_fore_cyan(36);
const console_attribute adventure_game::consolea_fore_white(37);
const console_attribute adventure_game::consolea_back_black(40);
const console_attribute adventure_game::consolea_back_red(41);
const console_attribute adventure_game::consolea_back_green(42);
const console_attribute adventure_game::consolea_back_yellow(43);
const console_attribute adventure_game::consolea_back_blue(44);
const console_attribute adventure_game::consolea_back_magenta(45);
const console_attribute adventure_game::consolea_back_cyan(46);
const console_attribute adventure_game::consolea_back_white(47);
#else
const console_attribute adventure_game::consolea_normal(77777);
const console_attribute adventure_game::consolea_fore_black(0);
const console_attribute adventure_game::consolea_fore_red(12);
const console_attribute adventure_game::consolea_fore_green(10);
const console_attribute adventure_game::consolea_fore_yellow(14);
const console_attribute adventure_game::consolea_fore_blue(9);
const console_attribute adventure_game::consolea_fore_magenta(13);
const console_attribute adventure_game::consolea_fore_cyan(11);
const console_attribute adventure_game::consolea_fore_white(15);
const console_attribute adventure_game::consolea_back_black(0);
const console_attribute adventure_game::consolea_back_red(0);
const console_attribute adventure_game::consolea_back_green(0);
const console_attribute adventure_game::consolea_back_yellow(0);
const console_attribute adventure_game::consolea_back_blue(0);
const console_attribute adventure_game::consolea_back_magenta(0);
const console_attribute adventure_game::consolea_back_cyan(0);
const console_attribute adventure_game::consolea_back_white(0);
#endif

#if defined(ADVENTUREGAME_LINUX) || defined(ADVENTUREGAME_WIN32)

our_ostream_buffer::our_ostream_buffer()
    : _attrib(consolea_normal)
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
    _trigger = false;
}
streambuf::int_type our_ostream_buffer::overflow(int_type ch)
{
    // handle color
    if (_trigger)
        _applyAttribute();
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
    // handle color
    if (_trigger)
        _applyAttribute();
    // write a buffer
#ifdef ADVENTUREGAME_LINUX
    return write(_fdOutput,data,n);
#else
    DWORD bytesOut;
    ::WriteFile(_hOutput,data,n,&bytesOut,NULL);
    return streamsize(bytesOut);
#endif
}
void our_ostream_buffer::_applyAttribute()
{
#ifdef ADVENTUREGAME_LINUX
    string s = "\033[1;";
    stringstream ss;
    ss << int(_attrib.value);
    s += ss.str();
    s.push_back('m');
    write(_fdOutput,s.c_str(),s.length());
#else
   if (_attrib == consolea_normal)
       _attrib = _wAttributesOriginal;
   ::SetConsoleTextAttribute(_hOutput,_attrib.value);
#endif
   _trigger = false;
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
    if (bufSz == 0)
        return;
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
        *this << ""; // put blank buffer to enforce attribute change
    }
}

static our_ostream_buffer theOutputStreamBuffer;
our_ostream adventure_game::exCout(theOutputStreamBuffer);

#else
// share stream buffers with 'cout'
our_ostream adventure_game::exCout( cout.rdbuf() );

#endif

// shared functionality for all compile-modes
// class adventure_game::our_stream
our_ostream& adventure_game::operator <<(our_ostream& stream,char c)
{
    static_cast<ostream&>(stream).put(c);
    return stream;
}
our_ostream& adventure_game::operator <<(our_ostream& stream,unsigned char c)
{
    static_cast<ostream&>(stream).put(c);
    return stream;
}
our_ostream& adventure_game::operator <<(our_ostream& stream,short s)
{
    static_cast<ostream&>(stream) << s;
    return stream;
}
our_ostream& adventure_game::operator <<(our_ostream& stream,unsigned short c)
{
    static_cast<ostream&>(stream).put(c);
    return stream;
}
our_ostream& adventure_game::operator <<(our_ostream& stream,int i)
{
    static_cast<ostream&>(stream) << i;
    return stream;
}
our_ostream& adventure_game::operator <<(our_ostream& stream,unsigned int c)
{
    static_cast<ostream&>(stream).put(c);
    return stream;
}
our_ostream& adventure_game::operator <<(our_ostream& stream,long l)
{
    static_cast<ostream&>(stream) << l;
    return stream;
}
our_ostream& adventure_game::operator <<(our_ostream& stream,unsigned long c)
{
    static_cast<ostream&>(stream).put(c);
    return stream;
}
our_ostream& adventure_game::operator <<(our_ostream& stream,const char* pStr)
{
    static_cast<ostream&>(stream) << pStr;
    return stream;
}
our_ostream& adventure_game::operator <<(our_ostream& stream,const string& s)
{
    static_cast<ostream&>(stream) << s;
    return stream;
}
our_ostream& adventure_game::operator <<(our_ostream& stream,console_attribute a)
{
    stream.set_attribute(a);
    return stream;
}
