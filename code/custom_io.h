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
    struct console_attribute
    {
        friend class our_ostream_buffer;
        friend bool operator ==(console_attribute,console_attribute);
        friend bool operator !=(console_attribute,console_attribute);

        console_attribute(unsigned short initial);
        console_attribute& operator =(unsigned short);
    private:
        unsigned short value;
    };

    // operator support
    bool operator ==(console_attribute,console_attribute);
    bool operator !=(console_attribute,console_attribute);

    // supported color constants
    extern const console_attribute consolea_normal;
    extern const console_attribute consolea_fore_black;
    extern const console_attribute consolea_fore_red;
    extern const console_attribute consolea_fore_green;
    extern const console_attribute consolea_fore_yellow;
    extern const console_attribute consolea_fore_blue;
    extern const console_attribute consolea_fore_magenta;
    extern const console_attribute consolea_fore_cyan;
    extern const console_attribute consolea_fore_white;
    extern const console_attribute consolea_back_black;
    extern const console_attribute consolea_back_red;
    extern const console_attribute consolea_back_green;
    extern const console_attribute consolea_back_yellow;
    extern const console_attribute consolea_back_blue;
    extern const console_attribute consolea_back_magenta;
    extern const console_attribute consolea_back_cyan;
    extern const console_attribute consolea_back_white;

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
    };

#endif

    // let's use this stream object
    // instead of 'std::cout'
    extern our_ostream exCout; // extended cout

    // stream output overloads
    our_ostream& operator <<(our_ostream&,char);
    our_ostream& operator <<(our_ostream&,unsigned char);
    our_ostream& operator <<(our_ostream&,short);
    our_ostream& operator <<(our_ostream&,unsigned short);
    our_ostream& operator <<(our_ostream&,int);
    our_ostream& operator <<(our_ostream&,unsigned int);
    our_ostream& operator <<(our_ostream&,long);
    our_ostream& operator <<(our_ostream&,unsigned long);
    our_ostream& operator <<(our_ostream&,const char*);
    our_ostream& operator <<(our_ostream&,const std::string&);
    our_ostream& operator <<(our_ostream&,console_attribute);
}

#endif
