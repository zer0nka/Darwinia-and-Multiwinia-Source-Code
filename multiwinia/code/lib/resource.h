/*
 * RESOURCE SYSTEM
 *
 */

#ifndef _included_resource_h
#define _included_resource_h

#include <unrar.h>
#include <string>

#include "lib/tosser/btree.h"
#include "lib/tosser/llist.h"
#include "lib/tosser/fast_darray.h"
#include "lib/tosser/hash_table.h"
#include "lib/runnable.h"
#include "lib/netlib/net_lib.h"

#ifdef TARGET_OS_MACOSX
	#include "hash_map_darwin.h"
#else
	#include <hash_map>
	using stdext::hash_map;
#endif


class Shape;
class BitmapRGBA;
class TextReader;
class BinaryReader;
class SoundStreamDecoder;
#ifdef USE_SEPULVEDA_HELP_TUTORIAL
    class GestureDemo;
#endif
class Resource;
class TextFileWriter;
class Runnable;

class Resource
{
protected:
	struct TextureInfo {
		TextureInfo( int _id, int _width, int _height );

		int m_id;
		int m_width; 
		int m_height;
	};

	NetMutex					m_mutex;
	unsigned int				m_nameSeed;

	// The RAR archive decompressed into RAM
	HashTable<MemMappedFile *>	m_resourceFiles;

	// Bitmaps that have been registered with the resource system, so that
	// they can be used as if they had been loaded from disk or the archive.
	// USUALLY USED for AUTOGENERATED bitmaps, so that the resource system
	// can regenerate textures for them when the OpenGL context is destroyed.
	HashTable<BitmapRGBA *>		m_bitmaps;

	HashTable<int>				m_displayLists;
    
	typedef hash_map< std::string, TextureInfo *> TextureHash;
	TextureHash					m_textures;	

	HashTable<Shape *>			m_shapes;
#ifdef USE_SEPULVEDA_HELP_TUTORIAL
	HashTable<GestureDemo *>	m_gestureDemos;
#endif

    char                        *m_modName;

	int WildCmp					( char const *_wild, char const *_string );
	TextureInfo * ProcessBmp	( BitmapRGBA &_bmp, int _flags );

public:
	// *** Initialisation/Destruction ***
    Resource();
	~Resource();
    void            ParseArchive		( char const *_dataFile, char const *_password);

	// *** Bitmaps ***
    void            AddBitmap			(char const *_name, BitmapRGBA const &_bmp);
	BitmapRGBA const*GetBitmap			(char const *_name);
	void			DeleteBitmap		(char const *_name);

	// *** Textures ***
	enum {
		WithMipmaps		= 0x1,
		WithMask		= 0x2,
		WithAlpha		= 0x4,
		WithCompression = 0x8
	};

	int             GetTexture			(char const *_name, bool _mipMapping=true, bool _masked=true, bool _compressed=false);
	int				GetTextureWithFlags (char const *_name, int _flags );
    int             GetTextureWithAlpha (char const *_name);
    bool            DoesTextureExist    (char const *_name);
	void			DeleteTexture       (char const *_name);  
	void			DeleteTextureAsync	(char const *_name);
	bool			GetTextureInfo		(char const *_name, int &_width, int &_height);
	
	// *** Files ***
	MemMappedFile	*GetUncompressedFile(char const *_filename);
	TextReader		*GetTextReader	    (std::string const &_filename);	// Caller must delete the TextReader when done
	TextReader		*GetTextReader	    (char const *_filename);	// Caller must delete the TextReader when done
	BinaryReader	*GetBinaryReader    (char const *_filename);	// Caller must delete the BinaryReader when done
    TextFileWriter      *GetTextFileWriter      (char const *_filename, bool _encrypt);

	// *** Shapes ****
    void            AddShape            (Shape *_shape, char const *_name );
	Shape			*GetShape			(char const *_name, bool _makeNew = true);		// Never produces an animatable shape because the one shape is shared between all people who call this function with the same shape name. If you want an animatable shape, call GetShapeCopy
	Shape			*GetShapeCopy		(char const *_name, bool _animating, bool _buildDisplayList = true );
    bool            DoesShapeExist      ( const char *_filename );

	// *** Normal resources ***
	SoundStreamDecoder *GetSoundStreamDecoder(char const *_filename);	// Caller must delete the decoder when done
#ifdef USE_SEPULVEDA_HELP_TUTORIAL
	GestureDemo		*GetGestureDemo		(char const *_name);
#endif
	
	// *** Display lists ***
	int				CreateDisplayList	(char const *_name);	// Adds _name to the hashtable and calls glGenLists
	int				CreateDisplayListAsync(char const *_name, const Runnable &_render, const Runnable &_before = NoOp(), const Runnable &_after = NoOp() );
	int				CreateDisplayList(char const *_name, const Runnable &_render, const Runnable &_before, const Runnable &_after );

	int				GetDisplayList		(char const *_name);	// Returns -1 if _name doesn't exist

	void			DeleteDisplayList	(char const *_name);	// Removes _name from the hashtable and calls glDeleteLists
	void			DeleteDisplayListAsync(char const *_name);
	void			DeleteDisplayListAsync( int _id );

    void			FlushOpenGlState	();
	void			RegenerateOpenGlState();

	// Returns a unique name that can be used to identify autogenerated resources. It is the caller's 
	// responsibility to delete the name later. Use "delete []" NOT "free".
	char			*GenerateName		();	

    void            LoadMod             (char const *_modName);
    bool            IsModLoaded         ();
    char            *GetBaseDirectory   ();
	const char      *GetModName			();

	LList <char *> *ListResources(char const *_dir, char const *_filter, bool _longResults = true);

	bool			FileExists( const char *_file );
	bool			SoundExists( const char *_file );
};



#endif
