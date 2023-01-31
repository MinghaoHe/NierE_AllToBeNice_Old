//
// Created by minghaohe on 2023/1/20.
//

#include "text_render.h"

#include <algorithm>

#include <3rdparty/ft2build.h>
#include FT_FREETYPE_H

namespace atn {
namespace render {

TextRender::TextRender() {}

TextRender::~TextRender() {}

void TextRender::InitText() {
  FT_Library ft;
  FT_Face ft_face;

  FT_Init_FreeType(&ft);
  // ftt path
  FT_New_Face(ft, "../res/font/NotoSansCJKsc-Regular.otf", 0, &ft_face);
  FT_Set_Pixel_Sizes(ft_face, 0, 48);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  for (FT_ULong c = 0; c < 128; ++c) {
    FT_Load_Char(ft_face, c, FT_LOAD_RENDER);
    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            ft_face->glyph->bitmap.width,
            ft_face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            ft_face->glyph->bitmap.buffer
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Character character = {
            texture,
            glm::ivec2(ft_face->glyph->bitmap.width, ft_face->glyph->bitmap.rows),
            glm::ivec2(ft_face->glyph->bitmap_left, ft_face->glyph->bitmap_top),
            static_cast<unsigned int>(ft_face->glyph->advance.x)
    };
    character_texture_map_.insert(std::make_pair(static_cast<char>(c), character));
  }
  glBindTexture(GL_TEXTURE_2D, 0);

  FT_Done_Face(ft_face);
  FT_Done_FreeType(ft);
}

void TextRender::UninitText() {
  std::for_each(character_texture_map_.begin(), character_texture_map_.end(),
                [](const auto &char_texture) {
                  glDeleteTextures(1, &char_texture.second.texture);
                });
}

const Character &TextRender::CharacterTextureObject(char c) const {
  return character_texture_map_.at(c);
}

}
}
