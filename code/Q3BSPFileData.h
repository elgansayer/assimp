/*
Open Asset Import Library (assimp)
----------------------------------------------------------------------

Copyright (c) 2006-2008, assimp team
All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the
following conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------
*/
#ifndef ASSIMP_Q3BSPFILEDATA_H_INC
#define ASSIMP_Q3BSPFILEDATA_H_INC

#include <vector>
#include <string.h> //memset
#include <string>

namespace Assimp {
namespace Q3BSP {

static const unsigned int CE_BSP_LIGHTMAPWIDTH = 128;
static const unsigned int CE_BSP_LIGHTMAPHEIGHT = 128;

static const unsigned int CE_BSP_LIGHTMAPSIZE = 128*128*3;  ///< = 128( width ) * 128 ( height ) * 3 ( channels / RGB ).
static const int VERION_Q3LEVEL = 46;                       ///< Supported version.

/// Geometric type enumeration
enum Q3BSPGeoType {
    Polygon = 1,
    Patch,
    TriangleMesh,
    Billboard
};

/// Integer vector.
struct ceVec3i {
    int x, y, z;
    ceVec3i(): x( 0 ), y( 0 ), z( 0 ) { /* empty */ }
    ceVec3i( int iX, int iY=0, int iZ=0) : x( iX ), y( iY ), z( iZ ) { /* empty */ }
};

/// the file header
struct sQ3BSPHeader {
    char strID[ 4 ]; ///< Should be "IBSP"
    int iVersion;    ///< 46 for standard levels
};

/// Describes an entry.
struct sQ3BSPLump
{
	signed int iOffset;    ///< Offset from start pointer of file
	signed int iSize;      ///< Size of part
};

struct vec2f
{
    float x,y;
};

struct vec3f
{
    float x, y, z;
};

/// Vertex of a Q3 level
struct sQ3BSPVertex
{
    vec3f vPosition;    ///< Position of vertex
    vec2f vTexCoord;    ///< (u,v) Texturecoordinate of detailtexture
    vec2f vLightmap;    ///< (u,v) Texturecoordinate of lightmap
    vec3f vNormal;      ///< vertex normale
    unsigned char bColor[ 4 ];          ///< Color in RGBA
};

/// A face in bsp format info
struct sQ3BSPFace
{
    int iTextureID;                 ///< Index in texture array
    int iEffect;                    ///< Index in effect array (-1 = no effect)
    int iType;                      ///< 1=Polygon, 2=Patch, 3=Mesh, 4=Billboard
    int iVertexIndex;               ///< Start index of polygon
    int iNumOfVerts;                ///< Number of vertices
    int iFaceVertexIndex;           ///< Index of first mesh vertex
    int iNumOfFaceVerts;            ///< number of mesh vertices
    int iLightmapID;                ///< Index to the light-map array
    int iLMapCorner[ 2 ];           ///< edge of the light-map in texture
    int iLMapSize[ 2 ];             ///< Size of the light-map stored on the texture
    vec3f vLMapPos;                 ///< 3D origin of the light-map
    vec3f vLMapVecs[ 2 ];           ///< 3D-s-t-vectors
    vec3f vNormal;                  ///< Polygon normals
    int patchWidth, patchHeight;    ///< bezier patch
	float subdivisions; //MOHAA
};

/// A quake3 texture name.
struct sQ3BSPTexture {
    char strName[ 64 ];     ///< Name of the texture without extension
	unsigned int iFlags;             ///< Not used
	unsigned int iContents;          ///< Not used
	unsigned int subdivisions; //MOHAA
	char fenceMaskImage[64]; //MOHAA
};

//mohaa imageBits[128][128][3];   // The RGB data in a 128x128 image

/// A light-map of the level, size 128 x 128, RGB components.
struct sQ3BSPLightmap {
    unsigned char bLMapData[ CE_BSP_LIGHTMAPSIZE ];
    sQ3BSPLightmap() {
        ::memset(bLMapData, 0, CE_BSP_LIGHTMAPSIZE );
    }
};

struct SubPatch {
    std::vector<size_t> indices;
    int lightmapID;
};

//quake3
/*
enum q3_eLumps {
    kEntities = 0,
    kTextures,
    kPlanes,
    kNodes,
    kLeafs,
    kLeafFaces,
    kLeafBrushes,
    kModels,
    kBrushes,
    kBrushSides,
    kVertices,
    kMeshVerts,
    kShaders,
    kFaces,
    kLightmaps,
    kLightVolumes,
    kVisData,
    kMaxLumps
};
*/
//mohaa
enum eLumps
{
	kShaders = 0,	// Stores texture information
	kPlanes = 1,	// Stores the splitting planes
	kLightmaps = 2,	// Stores the lightmaps for the level
	kFaces = 3,	// Stores the faces for the level
	kVertices = 4,	// Stores the level vertices
	kIndices = 5,	// Stores the indices for the level
	kLeafBrushes = 6,	// Stores the leaf's indices into the brushes
	kLeafFaces = 7,	// Stores the leaf's indices into the faces
	kLeafs = 8,	// Stores the leafs of the nodes
	kNodes = 9,	// Stores the BSP nodes
	kSideequations = 10,	// ---
	kBrushSides = 11,	// Stores the brush surfaces info
	kBrushes = 12,	// Stores the brushes info (for collision)
	kModels = 13,	// Stores the info of world models
	kEntities = 14,	// Stores player/object positions, etc...
	kVisData = 15,	// Stores PVS and cluster info (visibility)
	kLightGridPal = 16,	// Stores extra world lighting information (palette)
	kLightGridOfs = 17,	// Stores extra world lighting information (offsets)
	kLightGridDat = 18,	// Stores extra world lighting information (data)
	kSphereLight = 19,	// sphere lights
	kSphereLightVis = 20,	// sphere lights vis
	kUnknown1 = 21,	// not used in the code (?)
	kTerrain = 22,	// LOD terrain
	kTerrainIndices = 23,	// LOD terrain indices
	kStatModelDat = 24,	// Static Model Data
	kStatModelDef = 25,	// Static Model Defs
	kStatModelInd = 26,	// Static Model Indices
	kUnknown2 = 27,	// not used in the code (?)
	kMaxLumps				// A constant to store the number of lumps
};

struct Q3BSPModel {
    std::vector<unsigned char> m_Data;
    std::vector<sQ3BSPLump*> m_Lumps;
    std::vector<sQ3BSPVertex*> m_Vertices;
    std::vector<sQ3BSPFace*> m_Faces;
    std::vector<int> m_Indices;
    std::vector<sQ3BSPTexture*> m_Textures;
    std::vector<sQ3BSPLightmap*> m_Lightmaps;
    std::vector<char> m_EntityData;
    std::string m_ModelName;

    Q3BSPModel() :
        m_Data(),
        m_Lumps(),
        m_Vertices(),
        m_Faces(),
        m_Indices(),
        m_Textures(),
        m_Lightmaps(),
        m_EntityData(),
        m_ModelName( "" )
    {
        // empty
    }

    ~Q3BSPModel() {
        for ( unsigned int i=0; i<m_Lumps.size(); i++ ) {
            delete m_Lumps[ i ];
        }
        for ( unsigned int i=0; i<m_Vertices.size(); i++ ) {
            delete m_Vertices[ i ];
        }
        for ( unsigned int i=0; i<m_Faces.size(); i++ ) {
            delete m_Faces[ i ];
        }
        for ( unsigned int i=0; i<m_Textures.size(); i++ ) {
            delete m_Textures[ i ];
        }
        for ( unsigned int i=0; i<m_Lightmaps.size(); i++ ) {
            delete m_Lightmaps[ i ];
        }

        m_Lumps.clear();
        m_Vertices.clear();
        m_Faces.clear();
        m_Textures.clear();
        m_Lightmaps.clear();
    }
};

} // Namespace Q3BSP
} // Namespace Assimp

#endif // ASSIMP_Q3BSPFILEDATA_H_INC
