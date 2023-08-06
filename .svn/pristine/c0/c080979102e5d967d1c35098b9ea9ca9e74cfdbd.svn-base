/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}


MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    // bulid the KDTree based on theTiles
    vector<Point<3>> datasets;
    map<Point<3>, int> tile_avg_map;
    int index = 0;
    for(const TileImage& tile: theTiles){
        Point<3> target_point = convertToLAB(tile.getAverageColor());
        datasets.push_back(target_point);
        tile_avg_map.insert(pair<Point<3>, int>(target_point, index++));
    }
    KDTree<3> tree = KDTree<3>(datasets);

    // creat MosaicCanvas on heap with same shape as theSource
    MosaicCanvas* result = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

    // find and draw the tile on mosaic
    for(int x = 0; x < theSource.getRows(); x++){
        for(int y = 0; y < theSource.getColumns(); y++){
            TileImage* match_tile = get_match_at_idx(tree,tile_avg_map, theTiles, theSource, x, y);
            result->setTile(x, y, match_tile);
        }
    }
    return result;
}


TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}