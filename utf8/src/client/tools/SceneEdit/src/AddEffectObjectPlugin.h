#ifndef __ADDEFFECTOBJECTPLUGIN_H__
#define __ADDEFFECTOBJECTPLUGIN_H__

#include "WXSceneListener.h"

namespace Fairy {

    class SceneManipulator;
   
	/** 场景中特效物体的指示器
	*/
    class AddEffectObjectPlugin : public SceneListener
    {
    public:

        AddEffectObjectPlugin(Fairy::SceneManipulator* sceneManipulator);

        virtual ~AddEffectObjectPlugin();

        //////////////////////////////////////////////////////////////////////////
        virtual void onSceneReset(void);
        virtual void onAddObject(const ObjectPtr& object);
        virtual void onRemoveObject(const ObjectPtr& object);
        virtual void onSelectObject(const ObjectPtr& object);
        virtual void onDeselectObject(const ObjectPtr& object);
        virtual void onDeselectAllObjects(void);
        virtual void onObjectPropertyChanged(const ObjectPtr& object, const String& name);
		virtual void onSelectableChanged(const Ogre::String& objType, bool bSelectable = true);
		virtual void onSelectableChanged(const ObjectPtr& object, bool bSelectable = true);

    protected:

        class Indicator;

        typedef std::map<ObjectPtr, Indicator *> Indicators;
        Indicators mIndicators;

        Fairy::SceneManipulator* mSceneManipulator;
    };
}

#endif