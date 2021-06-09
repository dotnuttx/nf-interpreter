//
// Copyright (c) .NET Foundation and Contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//
#ifndef NANOCLR_PARSEOPTIONS_H
#define NANOCLR_PARSEOPTIONS_H

#include <nanoCLR_Runtime.h>

////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(_WIN32) || defined(__linux__) || defined(__nuttx__)

struct CLR_RT_ParseOptions
{
    typedef std::map< std::string, CLR_RT_Buffer* > BufferMap;
    typedef BufferMap::iterator                      BufferMapIter;

    struct Parameter
    {
        const char* m_szName;
        const char* m_szDescription;

        Parameter( const char* szName, const char* szDescription );

        virtual bool Parse( const char* val ) = 0;
    };

    typedef std::vector< Parameter* > ParameterList;
    typedef ParameterList::iterator   ParameterListIter;

    CLR_RT_StringVector CommandLineArgs;

    //--//

    struct Parameter_Generic : Parameter
    {
        std::string m_data;

        Parameter_Generic( const char* szName, const char* szDescription );

        virtual bool Parse( const char* arg );
    };

    struct Parameter_String : Parameter
    {
        std::string  m_dataParsed;
        std::string* m_dataPtr;

        Parameter_String( std::string* data, const char* szName, const char* szDescription );

        virtual bool Parse( const char* arg );
    };

    struct Parameter_Boolean : Parameter
    {
        bool  m_dataParsed;
        bool* m_dataPtr;

        Parameter_Boolean( bool* data, const char* szName, const char* szDescription );

        virtual bool Parse( const char* arg );
    };

    struct Parameter_Integer : Parameter
    {
        int  m_dataParsed;
        int* m_dataPtr;

        Parameter_Integer( int* data, const char* szName, const char* szDescription );

        virtual bool Parse( const char* arg );
    };

    struct Parameter_Float : Parameter
    {
        float  m_dataParsed;
        float* m_dataPtr;

        Parameter_Float( float* data, const char* szName, const char* szDescription );

        virtual bool Parse( const char* arg );
    };

    //--//

    struct Command
    {
        const char*       m_szName;
        const char*       m_szDescription;
        ParameterList m_params;

        Command( const char* szName, const char* szDescription );

        virtual bool Parse( CLR_RT_StringVector& argv, size_t& pos, CLR_RT_ParseOptions& options );

        virtual HRESULT Execute();
    };

    typedef std::list< Command* > CommandList;
    typedef CommandList::iterator CommandListIter;

    //--//

    struct Command_SetFlag : Command
    {
        bool  m_dataParsed;
        bool* m_dataPtr;

        Command_SetFlag( bool* data, const char* szName, const char* szDescription );

        virtual bool Parse( CLR_RT_StringVector& argv, size_t& pos, CLR_RT_ParseOptions& options );
    };

    //--//

    bool        m_fVerbose;
    CommandList m_commands;

    //--//

    CLR_RT_ParseOptions();

    HRESULT ExtractOptionsFromFile( const char* szFileName );

    HRESULT ReprocessOptions();
    HRESULT ProcessOptions(                          CLR_RT_StringVector& vec );
    void    PushArguments ( int argc, char* argv[], CLR_RT_StringVector& vec );

    virtual void Usage();
};

#endif

#endif // NANOCLR_PARSEOPTIONS_H
