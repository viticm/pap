/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id actionbutton.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-24 10:39:18
 * @uses cegui extend falagard action button class.
 */
#ifndef PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_ACTIONBUTTON_H_
#define PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_ACTIONBUTTON_H_

#include <client/lib/CEGUI/standard/Base.h> //CEGUI STANDARD
#include <client/lib/CEGUI/standard/widgets/ButtonBase.h>
#include "client/lib/CEGUI/extend/falagard/actionbutton_properties.h"
#include "client/lib/CEGUI/extend/falagard/iactionbutton.h"

// Start of CEGUI namespace section
namespace CEGUI {

namespace extend {

namespace falagard {

struct AnimationRuntime;
class Animation;

class CEGUIEXPORT ActionButton : public ButtonBase, public IActionButton {
 public:
    /*!
    \brief
    EventArgs based class used for certain drag/drop notifications
    */
   class ActionButtonDragDropEventArgs : public WindowEventArgs {
    public:
      ActionButtonDragDropEventArgs(Window* wnd) : WindowEventArgs(wnd) {}
      //<! pointer to the FalagardActionButton window being dragged / dropped.
      FalagardActionButton*  dragDropItem;
   };

 public:
   //!< type name for this widget.
   static const utf8  WidgetTypeName[];
   //!< Namespace for global events 
   static const String EventNamespace;
   //!< Name of the event fired when the user begins dragging the thumb.
   static const String EventDragStarted;
   //!< Name of the event fired when the user releases the thumb.
   static const String EventDragEnded;
   //!< Event fired when the drag position has changed.
   static const String EventDragPositionChanged;
   //!< Event fired when dragging is enabled or disabled.
   static const String EventDragEnabledChanged;
   //!< Event fired when the drag pixel threshold is changed.
   static const String EventDragThresholdChanged;
   //!< Event fired when the drop target changes.
   static const String EventDragDropTargetChanged;
   //!< A ActionButton has been dragged over this window.
   static const String EventDropItemEnters;
   //!< A ActionButton has left this window.
   static const String EventDropItemLeaves;
   //!< A ActionButton was dropped on this Window.
   static const String EventDropItemDropped;
   //!< The button was clicked by right button.
   static const String EventRBClicked;
   static const String EventItemReSet;
    /*!
    \brief
    Constructor
    */
   ActionButton(const String& type, const String& name);
    /*!
    \brief
    Destructor
    */
   ~ActionButton();
   /*************************************************************************
   Public Interface to FalagardActionButton
   *************************************************************************/

   virtual void FirReSet(void);
   bool isEmpty() const { return d_empty; }
   void setEmpty(bool setting) { d_empty = setting; }

   bool isChecked() const { return d_checked; }
   void setChecked(bool checked) { d_checked = checked; }

   bool isGloom() const { return d_gloom; }
   void setGloom(bool isgloom) { d_gloom = isgloom; }

   bool isDefault(void) const { return d_default; }
   void setDefault(bool bDefault) { d_default = bDefault; }

   //Helper 
   void* getHelper(void) const { return d_OwnerItem; }
   void setHelper(void* pHelper) { d_OwnerItem = pHelper; }
   bool isPercentagePresent(void){ return (d_percentageImg) ? true : false; }

   //Character at corner
   /*
   \brief
   0 - TopLeft    1 - TopRight  2 - BotLeft    3 - BotRight
   */
   String32 getCornerChar(int nPos) const;
   void setCornerChar(int nPos, const String32& strChar );

   virtual void  setAnimation(const String& name, int totalTime, float percent);
   virtual void  setPercentageImage(const String& animationName, 
                                     int cur, 
                                     int total);
   virtual void  cleanAnimation(void);
   virtual void  cleanPercentageImage(void);
   virtual void  onParentSized(WindowEventArgs& e);
   virtual void  onSized(WindowEventArgs& e);
   void drawNormal(float z);
   /*!
   \brief
   Return whether dragging is currently enabled for this DragContainer.

   \return
   - true if dragging is enabled and the DragContainer may be dragged.
   - false if dragging is disabled and the DragContainer may not be dragged.
   */
   bool isDraggingEnabled(void) const { return d_draggingEnabled; }

   /*!
   \brief
   Set whether dragging is currently enabled for this DragContainer.

   \param setting
   - true to enable dragging so that the DragContainer may be dragged.
   - false to disabled dragging so that the DragContainer may not be dragged.

   \return
   Nothing.
   */
   void setDraggingEnabled(bool setting) { d_draggingEnabled = setting; }

   /*!
   \brief
   Return the current drag threshold in pixels.

   The drag threshold is the number of pixels that the mouse must be
   moved with the left button held down in order to commence a drag
   operation.

   \return
   float value indicating the current drag threshold value.
   */
   float getPixelDragThreshold(void) const { return d_dragThreshold; }

   /*!
   \brief
   Set the current drag threshold in pixels.

   The drag threshold is the number of pixels that the mouse must be
   moved with the left button held down in order to commence a drag
   operation.

   \param pixels
   float value indicating the new drag threshold value.

   \return
   Nothing.
   */
   void setPixelDragThreshold(float pixels) { d_dragThreshold = pixels; }

   /*!
   \brief
   Subscribes DragdropStarted Event.
   */
   virtual void  subscribeDragDropStartedEvent(Event::Subscriber subscriber);
   /*!
   \brief
   Subscribes MouseEnter Event.
   */
   virtual void  subscribeMouseEnterEvent(Event::Subscriber subscriber);
   /*!
   \brief
   Subscribes MouseLeave Event.
   */
   virtual void  subscribeMouseLeaveEvent(Event::Subscriber subscriber);

   /*!
   \brief
   Notify the action button in draging that the draggging is done!.
   */
   virtual void  notifyDragingEnd(void);

   /*!
   \brief
   Notify a action button drag drop in.
   */
   virtual void  notifyDragDrop_Droped(FalagardActionButton* pBtn);
   
   /*!
   \brief
   Set/Get Logic data (ActionItem)
   */
   virtual void setLogicItemData(void* pData)  { d_LogicData = pData; };
   virtual void* getLogicItemData(void) const { return d_LogicData; }

   /*!
   \brief 
   Set/Get drag accept name.
   */
   virtual const char* getDragAcceptName(void) const { 
     return d_dragAcceptName.c_str(); }
   virtual void setDragAcceptName(const String& value) { 
     d_dragAcceptName = value; }
   virtual void setFlashAnimation( const String& strAnimationName );
   virtual void setFlashEnable( bool bEnable ){ d_Flash = bEnable; };
   void setBackImage( const Image* pImage );
   void setUseDefaultTooltip( bool bUse ) { d_isUseDefaultTooltip = bUse; };
 protected:
   /*************************************************************************
   Implementation of abstract methods in Window
   *************************************************************************/
   virtual void  drawSelf(float z);

   /*************************************************************************
   Overrides for Event handler methods
   *************************************************************************/
   virtual void  initialise(void);
   virtual void  onMouseButtonBaseDown(MouseEventArgs& e);
   virtual void  onMouseButtonBaseUp(MouseEventArgs& e);
   virtual void  onMouseMove(MouseEventArgs& e);
   virtual void  onRBClicked(WindowEventArgs& e);
   virtual void  onClicked(WindowEventArgs& e);
   virtual void  updateSelf(float elapsed);
   virtual void  prepareBigchar(void);

   /*************************************************************************
   New Event handler methods
   *************************************************************************/

 protected:
   /*************************************************************************
   Protected Implementation Methods
   *************************************************************************/
   void drawCorner(float z);
   void drawAnimation(float z);
   void drawPercentageImg(float z);
   void drawDefault(float z);
   void drawFlash(float z );// 画闪光效果，

   struct ANIMATE {
     Animation* d_animation;
     int d_time_start;
     int d_time_total;
     const Image*  d_currentFrame;
     float d_alpha;
     ANIMATE() {
       d_animation = NULL;
       d_time_start = 0;
       d_time_total = 0;
       d_currentFrame = 0;
       d_alpha = 0;
     };
   };

   void  updateAnimation(ANIMATE& animation);
   void  updateAnimationFlash();

   /*!
   \brief
   Return a pointer to the Tooltip object used by this Window.  
   The value returned may point to the system default Tooltip, 
   a custom Window specific Tooltip, or be NULL.

   \return
   Pointer to a Tooltip based object, or NULL.
   */
   virtual Tooltip* getTooltip(void) const;

   /*!
   \brief
   Return whether the required minimum movement threshold before 
   initiating dragging has been exceeded.

   \param local_mouse
   Mouse position as a pixel offset from the top-left corner of this window.

   \return
   - true if the threshold has been exceeded and dragging should be initiated.
   - false if the threshold has not been exceeded.
   */    
   bool isDraggingThresholdExceeded(const Point& local_mouse);


   /*!
   \brief
   Return whether this window was inherited from the given class name 
    at some point in the inheritance heirarchy.

   \param class_name
   The class name that is to be checked.

   \return
   true if this window was inherited from \a class_name. false if not.
   */
   virtual bool testClassName_impl(const String& class_name) const {
     if (class_name==(const utf8*)"FalagardActionButton")  return true;
     return FalagardButtonBase::testClassName_impl(class_name);
   }
   Rect getActionArea();

   /*!
   \brief
   return true if "update" must be processed

   \return 
   */
   virtual bool isUpdateRequire(void) const { return true; }

 protected:
   /*************************************************************************
   Data
   *************************************************************************/
   void* d_LogicData;    //!< Logic data refrence store here.
   bool d_empty;      //!< True if button empty
   bool d_checked;      //!< True if button is checked
   bool d_gloom;      //!< True if button is gloom
   bool d_default;      //!< True if button is default action button
   void* d_OwnerItem;    // Helper
   bool d_Flash;      // 是不是需要闪烁

   bool d_draggingEnabled;  //!< True when dragging is enabled.
   bool d_leftMouseDown;    //!< True when left mouse button is down.
   bool d_dragging;         //!< true when being dragged.
   Point d_dragPoint;        //!< point we are being dragged at.
   float d_dragThreshold;    //!< Pixels mouse must move before 
                               //dragging commences.
   String d_dragAcceptName;  //!< The name of drag accept name.

   struct CORNER_CHAR {
      String32 d_Char;         //String at ActionButton Corner
   };

   CORNER_CHAR d_CornerChar_TopLeft;  //!< TopLeft Corner
   CORNER_CHAR d_CornerChar_TopRight;  //!< TopRight Corner
   CORNER_CHAR d_CornerChar_BotLeft;  //!< BottomLeft Corner
   CORNER_CHAR d_CornerChar_BotRight;  //!< BottomRight Corner

   MouseButtonBase d_ActiveButtonBase;      //!< MouseButtonBase that 
                                              //do "Clicked" event
   MouseButtonBase d_DragButtonBase;      //!< MouseButtonBase that 
                                               //do "Drag" event;

   ANIMATE d_animation1;        //!< ButtonBase animation layout1
   ANIMATE d_animationFlash;      // 闪烁动画
   bool d_CoolDown;      // 说明现在正是cool down 状态

   const Image* d_percentageImg;    //!< Image used to draw percentage image.

   RenderableImage d_BackImage;        //背景图片

   bool d_isUseDefaultTooltip;

 private:
   /*************************************************************************
   Static properties for the Spinner widget
   *************************************************************************/
   static ActionButtonProperties::Empty d_emptyProperty;
   static ActionButtonProperties::Checked  d_checkedProperty;
   static ActionButtonProperties::Gloom  d_gloomProperty;
   static ActionButtonProperties::Default d_defaultProperty;
   static ActionButtonProperties::CornerChar d_cornerCharProperty;
   static ActionButtonProperties::DraggingEnabled d_dragEnabledProperty;
   static ActionButtonProperties::DragThreshold d_dragThresholdProperty;
   static ActionButtonProperties::DragAcceptName d_dragAcceptNameProperty;
   static ActionButtonProperties::FlashAnimation d_flashAnimationProperty;
   static ActionButtonProperties::BackImage d_BackImageProperty;
   static ActionButtonProperties::UseDefaultTooltip 
     d_UseDefaultTooltipProperty;

   /*************************************************************************
   Implementation methods
   *************************************************************************/

   /*!
   \brief
   Adds properties specific to the DragContainer base class.

   \return
   Nothing.
   */
   void addActionButtonProperties(void);
  }; 

  /*!
  \brief
  WindowFactory for FalagardButtonBase type Window objects.
  */
class FALAGARDBASE_API ActionButtonFactory : public WindowFactory {
 public:
   ActionButtonFactory(void) : WindowFactory(ActionButton::WidgetTypeName) { }
   ~ActionButtonFactory(void){}
   Window* createWindow(const String& name);
   void destroyWindow(Window* window);
};

}; //namespace falagard

}; //namespace extend

}; //namespace CEGUI

#endif //PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_ACTIONBUTTON_H_
