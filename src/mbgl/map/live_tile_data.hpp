#ifndef MBGL_MAP_LIVE_TILE_DATA
#define MBGL_MAP_LIVE_TILE_DATA

#include <mbgl/map/tile.hpp>
#include <mbgl/map/tile_data.hpp>
#include <mbgl/geometry/elements_buffer.hpp>
#include <mbgl/geometry/fill_buffer.hpp>
#include <mbgl/geometry/icon_buffer.hpp>
#include <mbgl/geometry/line_buffer.hpp>
#include <mbgl/geometry/text_buffer.hpp>
#include <mbgl/util/geojsonvt.hpp>

//#include <iosfwd>
//#include <memory>
#include <unordered_map>

namespace mbgl {

class Bucket;
class Painter;
class SourceInfo;
class StyleLayer;
//class TileParser;
class GlyphAtlas;
class GlyphStore;
class SpriteAtlas;
class Sprite;
class Style;

class LiveTileData : public TileData {
    friend class LiveTileParser;

public:
    LiveTileData(Tile::ID const&,
                 float mapMaxZoom, util::ptr<Style>,
                 GlyphAtlas&, GlyphStore&,
                 SpriteAtlas&, util::ptr<Sprite>,
                 const SourceInfo&, FileSource &,
                 util::ptr<mapbox::util::geojsonvt::GeoJSONVT>& geojsonvt);
    ~LiveTileData();

    virtual void parse();
    virtual void render(Painter &painter, util::ptr<StyleLayer> layer_desc, const mat4 &matrix);
    virtual bool hasData(StyleLayer const& layer_desc) const;

protected:
    // Holds the actual geometries in this tile.
    FillVertexBuffer fillVertexBuffer;
    LineVertexBuffer lineVertexBuffer;
    IconVertexBuffer iconVertexBuffer;
    TextVertexBuffer textVertexBuffer;

    TriangleElementsBuffer triangleElementsBuffer;
    LineElementsBuffer lineElementsBuffer;
    PointElementsBuffer pointElementsBuffer;

    // Holds the buckets of this tile.
    // They contain the location offsets in the buffers stored above
    std::unordered_map<std::string, std::unique_ptr<Bucket>> buckets;
    
    GlyphAtlas& glyphAtlas;
    GlyphStore& glyphStore;
    SpriteAtlas& spriteAtlas;
    util::ptr<Sprite> sprite;
    util::ptr<Style> style;
    util::ptr<mapbox::util::geojsonvt::GeoJSONVT>& geojsonvt;

public:
    const float depth;
};

}

#endif