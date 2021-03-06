#ifndef INCLUDED_RENDER_UIMODEL_H
#define INCLUDED_RENDER_UIMODEL_H
#include "platform/i_platform.h"
#include "ui/i_ui.h"
#include "ui_renderer.h"
#include "sprite_phase.h"

class UiModelRepo;
class UiModel
{
protected:
    friend class UiModelRepo;
    UiModel() {}
public:
    virtual ~UiModel() {}
    virtual void CollectVertices( Widget const& Wdg, UiVertexInserter_t& Inserter )const;
    static glm::vec4 GetColor( Widget const& Wdg );
    static void ColoredBox( glm::vec4 const& Dim, glm::vec4 const& Col, UiVertexInserter_t& Inserter );
    static void TexturedBox( glm::vec4 const& Dim, SpritePhase const& Phase, glm::vec4 const& Col, UiVertexInserter_t& Inserter );
};

#endif//INCLUDED_RENDER_UIMODEL_H
