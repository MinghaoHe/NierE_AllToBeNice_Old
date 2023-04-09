//
// Created by minghaohe on 2023/1/14.
//

#ifndef NIERE_ALLTOBENICE_RANDER_RENDER_ENGINE_H
#define NIERE_ALLTOBENICE_RANDER_RENDER_ENGINE_H

#include <unordered_set>

#include <3rdparty/glfw/glfw3.h>

#include "atn/common/utility.h"
#include "atn/base/object.h"
#include "atn/base/window_context.h"
#include "atn/render/frame_buffer.h"
#include "atn/render/render_context.h"
#include "atn/render/screen_buffer.h"
#include "atn/render/shader.h"
#include "atn/render/text_render.h"

namespace atn {
namespace render {

class RenderEngine {
 public:
  RenderEngine(base::WindowContext &window_context,
               std::unordered_set<std::shared_ptr<base::Object>> &objects,
               std::unordered_map<std::string, std::shared_ptr<base::Object>>
                   &global_objects_cache_map);

  ~RenderEngine() noexcept;

  void InitRender();

  void InitGlobalRenderEnvironment();

  void UninitRender();

  void Tick();

  RenderContext &GetRenderContext();

  std::shared_ptr<TextRender> GetTextRender();

  void FrameBufferSizeCallback(GLFWwindow *window, int width, int height);

 private:
  void InitFrameBuffers();
  void UninitFrameBuffers();
  void ClearFrameBuffers();

 private:
  base::WindowContext &window_context_;
  std::unordered_set<std::shared_ptr<base::Object>> &objects_;
  std::unordered_map<std::string, std::shared_ptr<base::Object>>
      &global_objects_cache_map_;
  RenderContext render_context_;
  std::shared_ptr<TextRender> text_render_;
  std::vector<FrameBuffer> frame_buffers_;
  ScreenBuffer screen_buffer_;

  DISALLOW_COPY_AND_ASSIGN(RenderEngine);
};

}  // namespace render
}  // namespace atn

#endif  // NIERE_ALLTOBENICE_RANDER_RENDER_ENGINE_H
