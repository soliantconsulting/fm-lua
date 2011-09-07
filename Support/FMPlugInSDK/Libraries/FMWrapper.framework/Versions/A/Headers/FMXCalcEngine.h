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

#ifndef _h_DBCalcEngine_
#define _h_DBCalcEngine_

#include "FMWrapper/FMXClient.h"

extern "C++"
{
    namespace fmx
    {
        class Text;
        class FixPt;
        class DateTime;
        class BinaryData;
    	class Data;
    	class DataVect;
    	class ExprEnv;

        FMX_PROCPTR( errcode, ExtPluginType ) ( short functionId, const ExprEnv& env, const DataVect& parms, Data& result );

        class DataVect
        {
        public:
            inline ulong Size () const;
            inline void Clear ();
            inline bool IsEmpty () const;
            inline void PushBack ( const Data &data );
            inline Data *PopBack ();
            inline const Data &At ( ulong position ) const;
            inline const Text &AtAsText ( ulong position ) const;
            inline const FixPt &AtAsNumber ( ulong position ) const;
            inline const DateTime &AtAsDate ( ulong position ) const;
            inline const DateTime &AtAsTime ( ulong position ) const;
            inline const DateTime &AtAsTimeStamp ( ulong position ) const;
            inline bool AtAsBoolean ( ulong position ) const;
            inline const BinaryData &AtAsBinaryData ( ulong position ) const;
            inline void operator delete ( void *obj );

        private:
            DataVect ();
            DataVect ( const DataVect& other );

        };

        class RowVect
		{
		public:
			inline ulong Size () const;
			inline bool IsEmpty () const;
			inline const DataVect &At ( ulong position ) const;
			inline void operator delete ( void *obj );

        private:
            RowVect ();
            RowVect ( const RowVect& other );

		};

        class ExprEnv
        {
        public:

			enum
			{
				kMayEvaluateOnServer	= 0x00000001,	// If this flag is not set then calcs containing the function will not be
														// evaluated on host as part of a find operation on an unstored calculation
														// field. Instead the client will be doing all the evaluations of calculations
														// to create the found set. If this flag is set then the plug-in must also
														// be loaded on the host.

				kDisplayCalcFields		= 0x00000100,	// Calculated fields
				kDisplayAutoEnter		= 0x00000200,	// Auto enter calculation
				kDisplayValidation		= 0x00000400,	// Validation by calculation
				kDisplayCustomFunctions	= 0x00000800,	// Custom function definition
				kDisplayPrivileges		= 0x00001000,	// Row level access calculations
				kDisplayInFuture1		= 0x00002000,	// As yet undefined calculation dialog
				kDisplayInFuture2		= 0x00004000,	// As yet undefined calculation dialog
				kDisplayGeneric			= 0x00008000,	// Dialog used by scripting and replace
				kDisplayInAllDialogs	= 0x0000FF00
			};

            inline errcode Evaluate ( const Text &expression, Data &result ) const;
 
			// Original SQL interface
            inline errcode ExecuteSQL ( const Text &expression, Data &result, ushort colSep, ushort rowSep ) const;

			// Experimental SQL interface: use with caution
            inline errcode ExecuteFileSQL ( const Text &expression, const Text &filename, const DataVect &parameters, RowVect& result ) const;

            // Dynamic Registration of Plug-in Functions
			//
			// RegisterExternalFunction enables the plug-in to register a function with the application,
			// so that function appears in the calculation dialog in the application.
			//
			// "pluginId" should be the unique four-digit identifier for your plug-in that you use for the "options" string.
			// "functionId" is the unique cookie that you can use to represent which function was called, it will be passed back to the
			//    registered function as the first parameter (see the parameter of the same name in "ExtPluginType").
			// "functionName" is the name of the function as it should appear in the calculation formula.
			// "functionPrototype" is the suggested syntax that will appear in the list of functions in the calculation dialog.
			// "minArgs" is the number of required parameters for the function.  0 is the smallest valid value.
			// "maxArgs" is the maximum number of parameters that they user should be able to specify in the calculation dialog
			//     and still have correct syntax usage for the function.  Use -1 to allow a variable number of parameters up to the
			//     number supported by calculation formulas in the application.
			// "typeFlags" is options for the function.  Currently only represents where the function will appear in the various kinds
			//     of calculation dialogs in the application.  See the enum above.
			// "funcPtr" is the pointer to the function that must match the signature defined by ExtPluginType.
			//
			//
			// UnRegisterExternalFunction removes the function entry from the list of external functions in any calculation dialog.
			//
            inline static errcode RegisterExternalFunction ( const QuadChar &pluginId, short functionId, const Text &functionName,
            							const Text &functionPrototype, short minArgs, short maxArgs, ulong typeFlags, ExtPluginType funcPtr );
            inline static errcode UnRegisterExternalFunction ( const QuadChar &pluginId, short functionId );
            inline void operator delete ( void *obj );

        private:
            ExprEnv ();
            ExprEnv ( const ExprEnv& other );

        };

        class DataVectAutoPtr : public std::auto_ptr<DataVect>
        {
			typedef DataVectAutoPtr	UpCaster;
        public:
            inline DataVectAutoPtr ();

        };

        class RowVectAutoPtr : public std::auto_ptr<RowVect>
        {
			typedef RowVectAutoPtr	UpCaster;
        public:
            inline RowVectAutoPtr ();

        };

        class ExprEnvAutoPtr : public std::auto_ptr<ExprEnv>
        {
			typedef ExprEnvAutoPtr	UpCaster;
        public:
            inline ExprEnvAutoPtr ();

        };

    }
}


// These functions are only useful for C-only environments or for porting to other languages (ex., Pascal).
extern "C"
{

    fmx::DataVect FMX_API *FM_DataVect_Constructor1 ( fmx::_fmxcpt &_x ) throw ();
	fmx::ulong FMX_API FM_DataVect_Size ( const void *_self, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_DataVect_Clear ( void *_self, fmx::_fmxcpt &_x ) throw ();
    bool FMX_API FM_DataVect_IsEmpty ( const void *_self, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_DataVect_PushBack ( void *_self, const fmx::Data &data, fmx::_fmxcpt &_x ) throw ();
    fmx::Data FMX_API *FM_DataVect_PopBack ( void *_self, fmx::_fmxcpt &_x ) throw ();
    const fmx::Data FMX_API &FM_DataVect_At ( const void *_self, fmx::ulong position, fmx::_fmxcpt &_x ) throw ();
    const fmx::Text FMX_API &FM_DataVect_AtAsText ( const void *_self, fmx::ulong position, fmx::_fmxcpt &_x ) throw ();
    const fmx::FixPt FMX_API &FM_DataVect_AtAsNumber ( const void *_self, fmx::ulong position, fmx::_fmxcpt &_x ) throw ();
    const fmx::DateTime FMX_API &FM_DataVect_AtAsDate ( const void *_self, fmx::ulong position, fmx::_fmxcpt &_x ) throw ();
    const fmx::DateTime FMX_API &FM_DataVect_AtAsTime ( const void *_self, fmx::ulong position, fmx::_fmxcpt &_x ) throw ();
    const fmx::DateTime FMX_API &FM_DataVect_AtAsTimeStamp ( const void *_self, fmx::ulong position, fmx::_fmxcpt &_x ) throw ();
    bool FMX_API FM_DataVect_AtAsBoolean ( const void *_self, fmx::ulong position, fmx::_fmxcpt &_x ) throw ();
    const fmx::BinaryData FMX_API &FM_DataVect_AtAsBinaryData ( const void *_self, fmx::ulong position, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_DataVect_Delete ( void *_self, fmx::_fmxcpt &_x ) throw ();

    fmx::RowVect FMX_API *FM_RowVect_Constructor1 ( fmx::_fmxcpt &_x ) throw ();
	fmx::ulong FMX_API FM_RowVect_Size ( const void *_self, fmx::_fmxcpt &_x ) throw ();
    bool FMX_API FM_RowVect_IsEmpty ( const void *_self, fmx::_fmxcpt &_x ) throw ();
    const fmx::DataVect FMX_API &FM_RowVect_At ( const void *_self, fmx::ulong position, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_RowVect_Delete ( void *_self, fmx::_fmxcpt &_x ) throw ();

    fmx::ExprEnv FMX_API *FM_ExprEnv_Constructor1 ( fmx::_fmxcpt &_x ) throw ();
    fmx::errcode FMX_API FM_ExprEnv_Evaluate ( const void *_self, const fmx::Text &expression, fmx::Data &result, fmx::_fmxcpt &_x ) throw ();
    fmx::errcode FMX_API FM_ExprEnv_ExecuteSQL ( const void *_self, const fmx::Text &expression, fmx::Data &result, fmx::ushort colSep, fmx::ushort rowSep, fmx::_fmxcpt &_x ) throw ();
	fmx::errcode FMX_API FM_ExprEnv_ExecuteFileSQL ( const void *_self, const fmx::Text &expression, const fmx::Text &filename, const fmx::DataVect &parameters, fmx::RowVect& result, fmx::_fmxcpt &_x ) throw ();
    fmx::errcode FMX_API FM_ExprEnv_RegisterExternalFunction ( const fmx::QuadChar &pluginId, short functionId, const fmx::Text &functionName, const fmx::Text &functionPrototype, short minArgs, short maxArgs, fmx::ulong typeFlags, fmx::ExtPluginType funcPtr, fmx::_fmxcpt &_x ) throw ();
    fmx::errcode FMX_API FM_ExprEnv_UnRegisterExternalFunction ( const fmx::QuadChar &pluginId, short functionId, fmx::_fmxcpt &_x ) throw ();
    void FMX_API FM_ExprEnv_Delete ( void *_self, fmx::_fmxcpt &_x ) throw ();

}


extern "C++"
{
    namespace fmx
    {
        inline ulong DataVect::Size () const
        {
            _fmxcpt _x;
            ulong _rtn = FM_DataVect_Size ( this, _x );
            _x.Check ();
            return _rtn;
        }
        inline void DataVect::Clear ()
        {
            _fmxcpt _x;
            FM_DataVect_Clear ( this, _x );
            _x.Check ();
        }
        inline bool DataVect::IsEmpty () const
        {
            _fmxcpt _x;
            bool _rtn = FM_DataVect_IsEmpty ( this, _x );
            _x.Check ();
            return _rtn;
        }
        inline void DataVect::PushBack ( const Data &data )
        {
            _fmxcpt _x;
            FM_DataVect_PushBack ( this, data, _x );
            _x.Check ();
        }
        inline Data *DataVect::PopBack ()
        {
            _fmxcpt _x;
            Data *_rtn = FM_DataVect_PopBack ( this, _x );
            _x.Check ();
            return _rtn;
        }
        inline const Data &DataVect::At ( ulong position ) const
        {
            _fmxcpt _x;
            const Data &_rtn = FM_DataVect_At ( this, position, _x );
            _x.Check ();
            return _rtn;
        }
        inline const Text &DataVect::AtAsText ( ulong position ) const
        {
            _fmxcpt _x;
            const Text &_rtn = FM_DataVect_AtAsText ( this, position, _x );
            _x.Check ();
            return _rtn;
        }
        inline const FixPt &DataVect::AtAsNumber ( ulong position ) const
        {
            _fmxcpt _x;
            const FixPt &_rtn = FM_DataVect_AtAsNumber ( this, position, _x );
            _x.Check ();
            return _rtn;
        }
        inline const DateTime &DataVect::AtAsDate ( ulong position ) const
        {
            _fmxcpt _x;
            const DateTime &_rtn = FM_DataVect_AtAsDate ( this, position, _x );
            _x.Check ();
            return _rtn;
        }
        inline const DateTime &DataVect::AtAsTime ( ulong position ) const
        {
            _fmxcpt _x;
            const DateTime &_rtn = FM_DataVect_AtAsTime ( this, position, _x );
            _x.Check ();
            return _rtn;
        }
        inline const DateTime &DataVect::AtAsTimeStamp ( ulong position ) const
        {
            _fmxcpt _x;
            const DateTime &_rtn = FM_DataVect_AtAsTimeStamp ( this, position, _x );
            _x.Check ();
            return _rtn;
        }
        inline bool DataVect::AtAsBoolean ( ulong position ) const
        {
            _fmxcpt _x;
            bool _rtn = FM_DataVect_AtAsBoolean ( this, position, _x );
            _x.Check ();
            return _rtn;
        }
        inline const BinaryData &DataVect::AtAsBinaryData ( ulong position ) const
        {
            _fmxcpt _x;
            const BinaryData &_rtn = FM_DataVect_AtAsBinaryData ( this, position, _x );
            _x.Check ();
            return _rtn;
        }
        inline void DataVect::operator delete ( void *obj )
        {
            _fmxcpt _x;
            FM_DataVect_Delete ( obj, _x );
            _x.Check ();
        }


        inline DataVectAutoPtr::DataVectAutoPtr ()
        {
            _fmxcpt _x;
            FMX_AUTOPTRRESET ( FM_DataVect_Constructor1 ( _x ) );
            _x.Check ();
        }

        inline ulong RowVect::Size () const
        {
            _fmxcpt _x;
            ulong _rtn = FM_RowVect_Size ( this, _x );
            _x.Check ();
            return _rtn;
        }
        inline bool RowVect::IsEmpty () const
        {
            _fmxcpt _x;
            bool _rtn = FM_RowVect_IsEmpty ( this, _x );
            _x.Check ();
            return _rtn;
        }
        inline const DataVect &RowVect::At ( ulong position ) const
        {
            _fmxcpt _x;
            const DataVect &_rtn = FM_RowVect_At ( this, position, _x );
            _x.Check ();
            return _rtn;
        }
        inline void RowVect::operator delete ( void *obj )
        {
            _fmxcpt _x;
            FM_RowVect_Delete ( obj, _x );
            _x.Check ();
        }

        inline RowVectAutoPtr::RowVectAutoPtr ()
        {
            _fmxcpt _x;
            FMX_AUTOPTRRESET ( FM_RowVect_Constructor1 ( _x ) );
            _x.Check ();
        }

        inline errcode ExprEnv::Evaluate ( const Text &expression, Data &result ) const
        {
            _fmxcpt _x;
            errcode _rtn = FM_ExprEnv_Evaluate ( this, expression, result, _x );
            _x.Check ();
            return _rtn;
        }
        inline errcode ExprEnv::ExecuteSQL ( const Text &expression, Data &result, ushort colSep, ushort rowSep ) const
		 {
            _fmxcpt _x;
            errcode _rtn = FM_ExprEnv_ExecuteSQL ( this, expression, result, colSep, rowSep, _x );
            _x.Check ();
            return _rtn;
        }
		inline errcode ExprEnv::ExecuteFileSQL ( const Text &expression, const Text &filename, const DataVect &parameters, RowVect& result ) const
		{
            _fmxcpt _x;
            errcode _rtn = FM_ExprEnv_ExecuteFileSQL ( this, expression, filename, parameters, result, _x );
            _x.Check ();
            return _rtn;
        }
        inline errcode ExprEnv::RegisterExternalFunction ( const QuadChar &pluginId, short functionId, const Text &functionName, const Text &functionPrototype, short minArgs, short maxArgs, ulong typeFlags, ExtPluginType funcPtr )
        {
            _fmxcpt _x;
            errcode _rtn = FM_ExprEnv_RegisterExternalFunction ( pluginId, functionId, functionName, functionPrototype, minArgs, maxArgs, typeFlags, funcPtr, _x );
            _x.Check ();
            return _rtn;
        }
        inline errcode ExprEnv::UnRegisterExternalFunction ( const QuadChar &pluginId, short functionId )
        {
            _fmxcpt _x;
            errcode _rtn = FM_ExprEnv_UnRegisterExternalFunction ( pluginId, functionId, _x );
            _x.Check ();
            return _rtn;
        }
        inline void ExprEnv::operator delete ( void *obj )
        {
            _fmxcpt _x;
            FM_ExprEnv_Delete ( obj, _x );
            _x.Check ();
        }

        inline ExprEnvAutoPtr::ExprEnvAutoPtr ()
        {
            _fmxcpt _x;
            FMX_AUTOPTRRESET ( FM_ExprEnv_Constructor1 ( _x ) );
            _x.Check ();
        }

    }
}


#endif /* _h_DBCalcEngine_ */
