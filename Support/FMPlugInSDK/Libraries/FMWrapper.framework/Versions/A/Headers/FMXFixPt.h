/*
 
 Copyright © 1998 - 2009  FileMaker, Inc.
 All rights reserved.
 
 FileMaker, Inc. grants you a non-exclusive limited license to use this file solely to enable
 licensees of FileMaker Pro Advanced to compile plug-ins for use with FileMaker products.
 Redistribution and use in source and binary forms, without modification, are permitted provided
 that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright notice, this list of
 conditions and the following disclaimer.
 
 * The name FileMaker, Inc. may not be used to endorse or promote products derived from
 this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY FILEMAKER, INC. ''AS IS'' AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL FILEMAKER, INC. BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 */

#ifndef _h_FixPt_
#define _h_FixPt_

#include "FMWrapper/FMXClient.h"

extern "C++"
{
    namespace fmx
    {
        class FixPt
        {
        public:

			enum
			{
				kDefltFixedPrecision = 16
			};
           
            inline void AssignInt ( long int that );
            inline void AssignDouble ( double that );
            inline void AssignFixPt ( const FixPt &that );
            inline bool operator == ( const FixPt &that ) const;
            inline bool operator != ( const FixPt &that ) const;
            inline bool operator < ( const FixPt &that ) const;
            inline bool operator <= ( const FixPt &that ) const;
            inline bool operator > ( const FixPt &that ) const;
            inline bool operator >= ( const FixPt &that ) const;
            inline void Increment ( long int n );
            inline void Decrement ( long int n );
            inline void Negate ();
            
            // Obtain and modify the decimal precision from the standard 16 digits. For more information, see SetPrecision calculation function in FileMaker Pro Advanced Help.
            inline int GetPrecision () const;
            inline void SetPrecision ( int precision );
            
            inline void Add ( const FixPt &arg, FixPt &result ) const;
            inline void Subtract ( const FixPt &arg, FixPt &result ) const;
            inline void Multiply ( const FixPt &arg, FixPt &result ) const;
            inline fmx::errcode Divide ( const FixPt &arg, FixPt &result ) const;
            inline bool AsBool () const;
            inline long int AsLong () const;
            inline double AsFloat () const;
            inline void operator delete ( void *obj );

        private:
            FixPt ();
            FixPt ( const FixPt &other );

        };

        class FixPtAutoPtr : public std::auto_ptr<FixPt>
        {
			typedef FixPtAutoPtr	UpCaster;
        public:
            inline FixPtAutoPtr ( long int val = 0, int precision = FixPt::kDefltFixedPrecision );
            inline FixPtAutoPtr ( long int val, const FixPt &precisionExample );

        };
    }
}


// These functions are only useful for C-only environments or for porting to other languages (ex., Pascal).
extern "C"
{
    fmx::FixPt FMX_API *FM_FixPt_Constructor1 ( long int val, int precision, fmx::_fmxcpt &_x ) throw ();
    fmx::FixPt FMX_API *FM_FixPt_Constructor2 ( long int val, const fmx::FixPt &precisionExample, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_FixPt_AssignInt ( void *_self, long int that, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_FixPt_AssignDouble ( void *_self, double that, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_FixPt_AssignFixPt ( void *_self, const fmx::FixPt &that, fmx::_fmxcpt &_x ) throw ();
    bool FMX_API FM_FixPt_operatorEQ ( const void *_self, const fmx::FixPt &that, fmx::_fmxcpt &_x ) throw ();
    bool FMX_API FM_FixPt_operatorNE ( const void *_self, const fmx::FixPt &that, fmx::_fmxcpt &_x ) throw ();
    bool FMX_API FM_FixPt_operatorLT ( const void *_self, const fmx::FixPt &that, fmx::_fmxcpt &_x ) throw ();
    bool FMX_API FM_FixPt_operatorLE ( const void *_self, const fmx::FixPt &that, fmx::_fmxcpt &_x ) throw ();
    bool FMX_API FM_FixPt_operatorGT ( const void *_self, const fmx::FixPt &that, fmx::_fmxcpt &_x ) throw ();
    bool FMX_API FM_FixPt_operatorGE ( const void *_self, const fmx::FixPt &that, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_FixPt_Increment ( void *_self, long int n, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_FixPt_Decrement ( void *_self, long int n, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_FixPt_Negate ( void *_self, fmx::_fmxcpt &_x ) throw ();
    int FMX_API FM_FixPt_GetPrecision ( const void *_self, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_FixPt_SetPrecision ( void *_self, int precision, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_FixPt_Add ( const void *_self, const fmx::FixPt &arg, fmx::FixPt &result, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_FixPt_Subtract ( const void *_self, const fmx::FixPt &arg, fmx::FixPt &result, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_FixPt_Multiply ( const void *_self, const fmx::FixPt &arg, fmx::FixPt &result, fmx::_fmxcpt &_x ) throw ();
    fmx::errcode FMX_API FM_FixPt_Divide ( const void *_self, const fmx::FixPt &arg, fmx::FixPt &result, fmx::_fmxcpt &_x ) throw ();
    bool FMX_API FM_FixPt_AsBool ( const void *_self, fmx::_fmxcpt &_x ) throw ();
    long int FMX_API FM_FixPt_AsLong ( const void *_self, fmx::_fmxcpt &_x ) throw ();
    double FMX_API FM_FixPt_AsFloat ( const void *_self, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_FixPt_Delete ( void *_self, fmx::_fmxcpt &_x ) throw ();

}


extern "C++"
{
    namespace fmx
    {
        inline void FixPt::AssignInt ( long int that )
        {
            _fmxcpt _x;
            FM_FixPt_AssignInt ( this, that, _x );
            _x.Check ();
        }
        inline void FixPt::AssignDouble ( double that )
        {
            _fmxcpt _x;
            FM_FixPt_AssignDouble ( this, that, _x );
            _x.Check ();
        }
        inline void FixPt::AssignFixPt ( const FixPt &that )
        {
            _fmxcpt _x;
            FM_FixPt_AssignFixPt ( this, that, _x );
            _x.Check ();
        }
        inline bool FixPt::operator == ( const FixPt &that ) const
        {
            _fmxcpt _x;
            bool _rtn = FM_FixPt_operatorEQ ( this, that, _x );
            _x.Check ();
            return _rtn;
        }
        inline bool FixPt::operator != ( const FixPt &that ) const
        {
            _fmxcpt _x;
            bool _rtn = FM_FixPt_operatorNE ( this, that, _x );
            _x.Check ();
            return _rtn;
        }
        inline bool FixPt::operator < ( const FixPt &that ) const
        {
            _fmxcpt _x;
            bool _rtn = FM_FixPt_operatorLT ( this, that, _x );
            _x.Check ();
            return _rtn;
        }
        inline bool FixPt::operator <= ( const FixPt &that ) const
        {
            _fmxcpt _x;
            bool _rtn = FM_FixPt_operatorLE ( this, that, _x );
            _x.Check ();
            return _rtn;
        }
        inline bool FixPt::operator > ( const FixPt &that ) const
        {
            _fmxcpt _x;
            bool _rtn = FM_FixPt_operatorGT ( this, that, _x );
            _x.Check ();
            return _rtn;
        }
        inline bool FixPt::operator >= ( const FixPt &that ) const
        {
            _fmxcpt _x;
            bool _rtn = FM_FixPt_operatorGE ( this, that, _x );
            _x.Check ();
            return _rtn;
        }
        inline void FixPt::Increment ( long int n )
        {
            _fmxcpt _x;
            FM_FixPt_Increment ( this, n, _x );
            _x.Check ();
        }
        inline void FixPt::Decrement ( long int n )
        {
            _fmxcpt _x;
            FM_FixPt_Decrement ( this, n, _x );
            _x.Check ();
        }
        inline void FixPt::Negate ()
        {
            _fmxcpt _x;
            FM_FixPt_Negate ( this, _x );
            _x.Check ();
        }
        inline int FixPt::GetPrecision () const
        {
            _fmxcpt _x;
            int _rtn = FM_FixPt_GetPrecision ( this, _x );
            _x.Check ();
            return _rtn;
        }
        inline void FixPt::SetPrecision ( int precision )
        {
            _fmxcpt _x;
            FM_FixPt_SetPrecision ( this, precision, _x );
            _x.Check ();
        }
        inline void FixPt::Add ( const FixPt &arg, FixPt &result ) const
        {
            _fmxcpt _x;
            FM_FixPt_Add ( this, arg, result, _x );
            _x.Check ();
        }
        inline void FixPt::Subtract ( const FixPt &arg, FixPt &result ) const
        {
            _fmxcpt _x;
            FM_FixPt_Subtract ( this, arg, result, _x );
            _x.Check ();
        }
        inline void FixPt::Multiply ( const FixPt &arg, FixPt &result ) const
        {
            _fmxcpt _x;
            FM_FixPt_Multiply ( this, arg, result, _x );
            _x.Check ();
        }
        inline errcode FixPt::Divide ( const FixPt &arg, FixPt &result ) const
        {
            _fmxcpt _x;
            errcode _rtn = FM_FixPt_Divide ( this, arg, result, _x );
            _x.Check ();
            return _rtn;
        }
        inline bool FixPt::AsBool () const
        {
            _fmxcpt _x;
            bool _rtn = FM_FixPt_AsBool ( this, _x );
            _x.Check ();
            return _rtn;
        }
        inline long int FixPt::AsLong () const
        {
            _fmxcpt _x;
            long int _rtn = FM_FixPt_AsLong ( this, _x );
            _x.Check ();
            return _rtn;
        }
        inline double FixPt::AsFloat () const
        {
            _fmxcpt _x;
            double _rtn = FM_FixPt_AsFloat ( this, _x );
            _x.Check ();
            return _rtn;
        }
        inline void FixPt::operator delete ( void *obj )
        {
            _fmxcpt _x;
            FM_FixPt_Delete ( obj, _x );
            _x.Check ();
        }

        inline FixPtAutoPtr::FixPtAutoPtr ( long int val, int precision )
        {
            _fmxcpt _x;
            FMX_AUTOPTRRESET ( FM_FixPt_Constructor1 ( val, precision, _x ) );
            _x.Check ();
        }
        inline FixPtAutoPtr::FixPtAutoPtr ( long int val, const FixPt &precisionExample )
        {
            _fmxcpt _x;
            FMX_AUTOPTRRESET ( FM_FixPt_Constructor2 ( val, precisionExample, _x ) );
            _x.Check ();
        }

    }
}


#endif /* _h_FixPt_ */
