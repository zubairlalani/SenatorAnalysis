#ifndef VECTOR_FIELD_GRAPHER_VECTOR_FIELD_SIMULATOR_H
#define VECTOR_FIELD_GRAPHER_VECTOR_FIELD_SIMULATOR_H

#include <cmath>

#include "../core/function_handler.h"

#include "cinder/ImageIo.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"
#include "cinder/gl/Vbo.h"
#include "cinder/Rand.h"


#include "particle_manager.h"


namespace vectorfield {

namespace visualizer {

using std::string;
using std::vector;

class FieldSimulator : public ci::app::App {
 public:

  /**
   * Initialize simulation/cinder screen
   */
  FieldSimulator();

  /**
   * Draws all parts of the app onto the cinder window
   * Gets called continuously
   */
  void draw() override;

  /**
   * Updates different parts of backend depending on
   * what is going on in the simulation
   * Note: Gets called before draw() every frame
   */
  void update() override;

  /**
   * Cinder method that sets important parameters up or performs actions
   * that only needed to be performed once
   * Ex: creating button panel
   */
  void setup() override;

  void mouseDrag(ci::app::MouseEvent event) override;

  void mouseUp(ci::app::MouseEvent event) override;

  void mouseDown(ci::app::MouseEvent event) override;

 private:

  const size_t kWindowSize = 700; // Size of the cinder window
  const size_t kGraphMargin = 50; // Dist from sides of window that graph axes are drawn
  //const size_t kInputBoxHeight = 100;
  const int kScale = 10; // Determines how many units an axis goes up to
  const int kVectorScale = 10; // Number of vectors that will be drawn
  const float kArrowHeight = 3.0f; // Height of arrowhead
  const float kArrowBase = 10.0f; // Distance that the base of the arrow spans

  float image_scaling_factor_ = .1f; // Relative size of the arrows
  /**
  * Performs an actions depending on which button is clicked
  * Drawing vector field, clearing vector field, etc
  * @param id - indicates which button is being pressed
  */
  void button(size_t id);

  ci::params::InterfaceGlRef mParams; // Used for user input

  string i_component_; // Representation of i-component of the vector field that user provided
  string j_component_; // Representation of j-component of the vector field that user provided
  string x_pos_;
  string y_pos_;

  glm::vec2 origin_; // Window coordinates of position (0, 0) of the graph axes
  double x_unit_; // Amount of pixels that a single x unit is
  double y_unit_; // Amount of pixels that a single y unit is

  ParticleManager particle_manager_; // Draws and updates all particles on screen
  std::map<std::pair<int, int>, glm::vec2> field_vectors_; // Maps coordinate points to their corresponding velocity vectors

  FunctionHandler function_handler_; // Computes all math involved

  glm::vec2 mouse_pos_;
  bool left_down_;
  bool in_range_;

  //ci::gl::VboMeshRef mesh;
  //ci::gl::BatchRef mBatch;
  //std::vector< glm::vec2 > vertices;
  //std::vector<size_t> indices;
  //ci::gl::VboMesh::Layout layout;

  std::vector<ci::vec4> mInstanceData;
  size_t                mInstanceCount;
  ci::gl::GlslProgRef       mGlslProg;
  ci::gl::VboRef            mInstanceVbo;
  ci::gl::VboMeshRef        mVboMesh;
  ci::gl::BatchRef          mBatch;

  ci::gl::GlslProgRef       mGlslProg2;
  ci::gl::BatchRef          mBatch2;
  ci::gl::VertBatchRef      vertBatch;

};

} // namespace visualizer
} // namespace vectorfield

#endif  // VECTOR_FIELD_GRAPHER_VECTOR_FIELD_SIMULATOR_H
