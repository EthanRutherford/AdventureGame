/* custom_io.h
 * Project: AdventureGame
 * Owner: Roger Gee
 * Brief: defines custom output ostream 'exCout' that supports nice things like
 * colors, buffering, ETC.
 */
#ifndef ADVENTUREGAME_CUSTOM_OSTREAM_H
#define ADVENTUREGAME_CUSTOM_OSTREAM_H
#include <iostream>

// prevent compiler warnings for unimplemented functions
// check compilation because Windows.h has one
#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P) (&P)
#endif

namespace adventure_game
{
#ifdef ADVENTUREGAME_LINUX
    enum console_attribute
    {
        consolea_normal = 0,
        consolea_fore_black = 30,
        consolea_fore_red = 31,
        consolea_fore_green = 32,
        consolea_fore_yellow = 33,
        consolea_fore_blue = 34,
        consolea_fore_magneta = 35,
        consolea_fore_cyan = 36,
        consolea_fore_white = 37,
        consolea_back_black = 40,
        consolea_back_red = 41,
        consolea_back_green = 42,
        consolea_back_yellow = 43,
        consolea_back_blue = 44,
        consolea_back_magenta = 45,
        consolea_back_cyan = 46,
        consolea_back_white = 47
    };
#else
    enum console_attribute
    {
        consolea_normal = 77777, // some value greater than 2^sizeof(WORD)
        consolea_fore_black = 0,
        consolea_fore_red = 12,
        consolea_fore_green = 10,
        consolea_fore_yellow = 14,
        consolea_fore_blue = 9,
        consolea_fore_magneta = 13,
        consolea_fore_cyan = 11,
        consolea_fore_white = 15,
        consolea_back_black = 0,
        consolea_back_red = 0,
        consolea_back_green = 0,
        consolea_back_yellow = 0,
        consolea_back_blue = 0,
        consolea_back_magenta = 0,
        consolea_back_cyan = 0,
        consolea_back_white = 0
    };
#endif

#if defined(ADVENTUREGAME_LINUX) || defined(ADVENTUREGAME_WIN32)
    class our_ostream;
    class our_ostream_buffer : public std::streambuf
    {
        friend class our_ostream;
        friend our_ostream& operator <<(our_ostream&,console_attribute);
    public:
        our_ostream_buffer();
    protected:
        virtual int_type overflow(int_type);
        virtual std::streamsize xsputn(const char*,std::streamsize);
    private:
#ifdef ADVENTUREGAME_WIN32
        void* _hOutput; // HANDLE
        unsigned short _wAttributesOriginal;
        unsigned short _colCnt, _rowCnt;
#else
        int _fdOutput; // descriptor
#endif
        console_attribute _attrib;
        bool _trigger;

        void _applyAttribute();
    };

    class our_ostream : public std::ostream
    {
    public:
        our_ostream(our_ostream_buffer&);

        void clear_screen();
        void set_attribute(console_attribute attrib);
        void restore_attribute()
        { set_attribute(consolea_normal); }

        // allow support for color codes in middle of 
        // ostream output expression
        our_ostream& operator <<(char);
        our_ostream& operator <<(short);
        our_ostream& operator <<(int);
        our_ostream& operator <<(long);
    private:
        our_ostream_buffer* _pBuf;
    };

#else

    // provide the same interface that allows compatibility
    // with the plain 'cout'
    class our_ostream : public std::ostream
    {
    public:
        our_ostream(std::streambuf* buffer)
            : std::ostream(buffer) {}

        // implement the same interface; but provide none
        // of the same functionality
        
        void clear_screen()
        { this->put('\n'); } // just use an endline if we cannot clear the screen
        void set_attribute(console_attribute)
        { } // do nothing
        void restore_attribute()
        { } // do nothing

        our_stream& operator <<(char);
        our_stream& operator <<(short);
        our_stream& operator <<(int);
        our_stream& operator <<(long);
    };

#endif

    // let's use this stream object
    // instead of 'std::cout'
    extern our_ostream exCout; // extended cout

    // stream output overloads
    our_ostream& operator <<(our_ostream&,const char*);
    our_ostream& operator <<(our_ostream&,const std::string&);
    our_ostream& operator <<(our_ostream&,console_attribute);
}

#endif
