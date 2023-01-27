//
// Created by minghaohe on 2023/1/20.
//

#ifndef NIERE_ALLTOBENICE_RENDER_TEXT_RENDER_H
#define NIERE_ALLTOBENICE_RENDER_TEXT_RENDER_H


#include <unordered_map>

#include <opengl/gl3.h>
#include <glm/glm.hpp>


namespace atn {
namespace render {

struct Character {
  GLuint texture;
  glm::ivec2 size;
  glm::ivec2 bearing;
  unsigned int advance;
};

class TextRender {
 public:
  TextRender();

  ~TextRender();


  void InitText();

  void UninitText();

  const Character& CharacterTextureObject(char c) const;

 private:
  std::unordered_map<char, Character> character_texture_map_;
};

}
}

#endif // NIERE_ALLTOBENICE_RENDER_TEXT_RENDER_H
