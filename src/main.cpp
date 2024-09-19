#include "layers/CreatorLayer.h"
#include "layers/LevelSearchLayer.h"
#include "layers/MenuLayer.h"
#include "layers/PauseLayer.h"
#include "layers/LevelInfoLayer.h"
#include "layers/EditorUI.h"
#include "CCMenuItemSpriteExtra.h"
#include <Geode/modify/CCNode.hpp>

//#define IN_PROGRESS

CCNode* CCNode_getChildByID(CCNode* self, std::string const& id) {

    if (!self) return nullptr; //cuz people are dumb, I gotta check if they're calling the method on a nullptr

    if (CCArray* children = typeinfo_cast<CCArray*>(self->getUserObject("page-children"_spr))) {
        for (CCNode* child : CCArrayExt<CCNode*>(children)) {
            if (child->getID() == id) {
                return child;
            }
        }
        return nullptr;
    }

    return self->getChildByID(id);
}

$execute {
    (void) Mod::get()->hook(
        reinterpret_cast<void*>(
            geode::addresser::getNonVirtual(
                geode::modifier::Resolve<std::string const&>::func(&CCNode::getChildByID)
            )
        ),
        &CCNode_getChildByID,
        "CCNode::getChildByID",
        tulip::hook::TulipConvention::Thiscall
    );
}