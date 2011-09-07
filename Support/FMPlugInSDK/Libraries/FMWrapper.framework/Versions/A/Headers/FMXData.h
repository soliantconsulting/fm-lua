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

#ifndef _h_Data_
#define _h_Data_

#include "FMWrapper/FMXClient.h"
#include "FMWrapper/FMXTextStyle.h"

extern "C++"
{
    namespace fmx
    {
        class Locale;
        class Text;
        class FixPt;
        class DateTime;
        class BinaryData;
		class ExprEnv;

        class Data
        {
        public:

			enum DataType
			{
				kDTInvalid,
				kDTText,
				kDTNumber,
				kDTDate,
				kDTTime,
				kDTTimeStamp,
				kDTBinary,
				kDTBoolean
			};

            inline bool IsEmpty () const;
            inline bool IsValid () const;
            inline bool IsFindRequest () const;
            inline void Clear ( DataType newNativeType = kDTInvalid );
            inline const Text &GetAsText () const;
            inline const FixPt &GetAsNumber () const;
            inline const DateTime &GetAsDate () const;
            inline const DateTime &GetAsTime () const;
            inline const DateTime &GetAsTimeStamp () const;
            inline bool GetAsBoolean () const;
            inline const BinaryData &GetBinaryData () const;
            inline const Locale &GetLocale () const;
            inline const DataType GetNativeType () const;
            inline void ConvertData ( DataType nativeType );
            inline errcode SetAsText ( const Text &textData, const Locale &sourceLocale, const DataType nativeType = kDTText );
            inline void SetAsNumber ( const FixPt &numericData, const DataType nativeType = kDTNumber );
            inline void SetAsDate ( const DateTime &dateData, const DataType nativeType = kDTDate );
            inline void SetAsTime ( const DateTime &timeData, const DataType nativeType = kDTTime );
            inline void SetAsTimeStamp ( const DateTime &timeStampData, const DataType nativeType = kDTTimeStamp );
            inline void SetDateTime ( const DateTime &dateTimeData, const DataType dateTimeType, const DataType nativeType );
            inline void SetBinaryData ( const BinaryData &binaryData, bool forceBinaryNativeType = true );
            inline void operator delete ( void *obj );

			// GetFontID will create a new id if the specified font name and font script has not been
			// used before in the database. A font id of zero is returned if the font could not be created.
			inline CharacterStyle::FontID GetFontID( const Text &fontName, CharacterStyle::FontScript fontScript, const ExprEnv &env );

			// GetFontInfo will return false if the given font id is not found in the database
			inline bool GetFontInfo( CharacterStyle::FontID font, Text &fontName, CharacterStyle::FontScript &fontScript, const ExprEnv &env ) const;

		private:
            Data ();
            Data ( const Data &other );

        };

        class DataAutoPtr : public std::auto_ptr<Data>
        {
			typedef DataAutoPtr	UpCaster;
        public:
            inline DataAutoPtr ();

        };
    }
}


// These functions are only useful for C-only environments or for porting to other languages (ex., Pascal).
extern "C"
{

    fmx::Data FMX_API *FM_Data_Constructor1 ( fmx::_fmxcpt &_x ) throw ();
    bool FMX_API FM_Data_IsEmpty ( const void *_self, fmx::_fmxcpt &_x ) throw ();
    bool FMX_API FM_Data_IsValid ( const void *_self, fmx::_fmxcpt &_x ) throw ();
    bool FMX_API FM_Data_IsFindRequest ( const void *_self, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_Data_Clear ( void *_self, long newNativeType, fmx::_fmxcpt &_x ) throw ();
    const fmx::Text FMX_API &FM_Data_GetAsText ( const void *_self, fmx::_fmxcpt &_x ) throw ();
    const fmx::FixPt FMX_API &FM_Data_GetAsNumber ( const void *_self, fmx::_fmxcpt &_x ) throw ();
    const fmx::DateTime FMX_API &FM_Data_GetAsDate ( const void *_self, fmx::_fmxcpt &_x ) throw ();
    const fmx::DateTime FMX_API &FM_Data_GetAsTime ( const void *_self, fmx::_fmxcpt &_x ) throw ();
    const fmx::DateTime FMX_API &FM_Data_GetAsTimeStamp ( const void *_self, fmx::_fmxcpt &_x ) throw ();
    bool FMX_API FM_Data_GetAsBoolean ( const void *_self, fmx::_fmxcpt &_x ) throw ();
    const fmx::BinaryData FMX_API &FM_Data_GetBinaryData ( const void *_self, fmx::_fmxcpt &_x ) throw ();
    const fmx::Locale FMX_API &FM_Data_GetLocale ( const void *_self, fmx::_fmxcpt &_x ) throw ();
    const long FMX_API FM_Data_GetNativeType ( const void *_self, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_Data_ConvertData ( void *_self, long nativeType, fmx::_fmxcpt &_x ) throw ();
    fmx::errcode FMX_API FM_Data_SetAsText ( void *_self, const fmx::Text &textData, const fmx::Locale &sourceLocale, long nativeType, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_Data_SetAsNumber ( void *_self, const fmx::FixPt &numericData, long nativeType, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_Data_SetAsDate ( void *_self, const fmx::DateTime &dateData, long nativeType, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_Data_SetAsTime ( void *_self, const fmx::DateTime &timeData, long nativeType, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_Data_SetAsTimeStamp ( void *_self, const fmx::DateTime &timeStampData, long nativeType, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_Data_SetDateTime ( void *_self, const fmx::DateTime &dateTimeData, long dateTimeType, long nativeType, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_Data_SetBinaryData ( void *_self, const fmx::BinaryData &binaryData, bool forceBinaryNativeType, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_Data_Delete ( void *_self, fmx::_fmxcpt &_x ) throw ();

    fmx::CharacterStyle::FontID FMX_API FM_Data_GetFontID ( void *_self, const fmx::Text &fontName, fmx::CharacterStyle::FontScript fontScript, const fmx::ExprEnv &env,  fmx::_fmxcpt &_x ) throw ();
    bool FMX_API FM_Data_GetFontInfo ( const void *_self, fmx::CharacterStyle::FontID font, fmx::Text &fontName, fmx::CharacterStyle::FontScript &fontScript, const fmx::ExprEnv &env, fmx::_fmxcpt &_x ) throw ();

}


extern "C++"
{
    namespace fmx
    {
        inline bool Data::IsEmpty () const
        {
            _fmxcpt _x;
            bool _rtn = FM_Data_IsEmpty ( this, _x );
            _x.Check ();
            return _rtn;
        }
        inline bool Data::IsValid () const
        {
            _fmxcpt _x;
            bool _rtn = FM_Data_IsValid ( this, _x );
            _x.Check ();
            return _rtn;
        }
        inline bool Data::IsFindRequest () const
        {
            _fmxcpt _x;
            bool _rtn = FM_Data_IsFindRequest ( this, _x );
            _x.Check ();
            return _rtn;
        }
        inline void Data::Clear ( DataType newNativeType )
        {
            _fmxcpt _x;
            FM_Data_Clear ( this, newNativeType, _x );
            _x.Check ();
        }
        inline const Text &Data::GetAsText () const
        {
            _fmxcpt _x;
            const Text &_rtn = FM_Data_GetAsText ( this, _x );
            _x.Check ();
            return _rtn;
        }
        inline const FixPt &Data::GetAsNumber () const
        {
            _fmxcpt _x;
            const FixPt &_rtn = FM_Data_GetAsNumber ( this, _x );
            _x.Check ();
            return _rtn;
        }
        inline const DateTime &Data::GetAsDate () const
        {
            _fmxcpt _x;
            const DateTime &_rtn = FM_Data_GetAsDate ( this, _x );
            _x.Check ();
            return _rtn;
        }
        inline const DateTime &Data::GetAsTime () const
        {
            _fmxcpt _x;
            const DateTime &_rtn = FM_Data_GetAsTime ( this, _x );
            _x.Check ();
            return _rtn;
        }
        inline const DateTime &Data::GetAsTimeStamp () const
        {
            _fmxcpt _x;
            const DateTime &_rtn = FM_Data_GetAsTimeStamp ( this, _x );
            _x.Check ();
            return _rtn;
        }
        inline bool Data::GetAsBoolean () const
        {
            _fmxcpt _x;
            bool _rtn = FM_Data_GetAsBoolean ( this, _x );
            _x.Check ();
            return _rtn;
        }
        inline const BinaryData &Data::GetBinaryData () const
        {
            _fmxcpt _x;
            const BinaryData &_rtn = FM_Data_GetBinaryData ( this, _x );
            _x.Check ();
            return _rtn;
        }
        inline const Locale &Data::GetLocale () const
        {
            _fmxcpt _x;
            const Locale &_rtn = FM_Data_GetLocale ( this, _x );
            _x.Check ();
            return _rtn;
        }
        inline const Data::DataType Data::GetNativeType () const
        {
            _fmxcpt _x;
            const DataType _rtn = static_cast<DataType>(FM_Data_GetNativeType ( this, _x ));
            _x.Check ();
            return _rtn;
        }
        inline void Data::ConvertData ( DataType nativeType )
        {
            _fmxcpt _x;
            FM_Data_ConvertData ( this, nativeType, _x );
            _x.Check ();
        }
        inline errcode Data::SetAsText ( const Text &textData, const Locale &sourceLocale, const DataType nativeType )
        {
            _fmxcpt _x;
            errcode _rtn = FM_Data_SetAsText ( this, textData, sourceLocale, nativeType, _x );
            _x.Check ();
            return _rtn;
        }
        inline void Data::SetAsNumber ( const FixPt &numericData, const DataType nativeType )
        {
            _fmxcpt _x;
            FM_Data_SetAsNumber ( this, numericData, nativeType, _x );
            _x.Check ();
        }
        inline void Data::SetAsDate ( const DateTime &dateData, const DataType nativeType )
        {
            _fmxcpt _x;
            FM_Data_SetAsDate ( this, dateData, nativeType, _x );
            _x.Check ();
        }
        inline void Data::SetAsTime ( const DateTime &timeData, const DataType nativeType )
        {
            _fmxcpt _x;
            FM_Data_SetAsTime ( this, timeData, nativeType, _x );
            _x.Check ();
        }
        inline void Data::SetAsTimeStamp ( const DateTime &timeStampData, const DataType nativeType )
        {
            _fmxcpt _x;
            FM_Data_SetAsTimeStamp ( this, timeStampData, nativeType, _x );
            _x.Check ();
        }
        inline void Data::SetDateTime ( const DateTime &dateTimeData, const DataType dateTimeType, const DataType nativeType )
        {
            _fmxcpt _x;
            FM_Data_SetDateTime ( this, dateTimeData, dateTimeType, nativeType, _x );
            _x.Check ();
        }
        inline void Data::SetBinaryData ( const BinaryData &binaryData, bool forceBinaryNativeType )
        {
            _fmxcpt _x;
            FM_Data_SetBinaryData ( this, binaryData, forceBinaryNativeType, _x );
            _x.Check ();
        }
        inline void Data::operator delete ( void *obj )
        {
            _fmxcpt _x;
            FM_Data_Delete ( obj, _x );
            _x.Check ();
        }

        inline DataAutoPtr::DataAutoPtr ()
        {
            _fmxcpt _x;
            FMX_AUTOPTRRESET ( FM_Data_Constructor1 ( _x ) );
            _x.Check ();
        }

		inline CharacterStyle::FontID Data::GetFontID( const Text &fontName, CharacterStyle::FontScript fontScript, const ExprEnv &env )
        {
            _fmxcpt _x;
            CharacterStyle::FontID _rtn = FM_Data_GetFontID ( this, fontName, fontScript, env, _x );
            _x.Check ();
			return _rtn;
        }
		inline bool Data::GetFontInfo( CharacterStyle::FontID font, Text &fontName, CharacterStyle::FontScript &fontScript, const ExprEnv &env ) const
        {
            _fmxcpt _x;
            bool _rtn = FM_Data_GetFontInfo ( this, font, fontName, fontScript, env, _x );
            _x.Check ();
			return _rtn;
        }
    }
}


#endif /* _h_Data_ */
