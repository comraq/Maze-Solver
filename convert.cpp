#include <boost/gil/image.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/extension/io/jpeg_io.hpp>

#include <string>

using namespace boost::gil;
 
const string MAZEPATH = "Mazes/";


int main() {

  rgb8_image_t img;
  jpeg_read_image(MAZEPATH + "SampleMaze1.jpg",img);

  gray8s_view_t view(img.dimensions());
  color_converted_view<gray8_pixel_t>(const_view(img), view);

  jpeg_write_view(MAZEPATH + "grey1.jpg", view);
 }
