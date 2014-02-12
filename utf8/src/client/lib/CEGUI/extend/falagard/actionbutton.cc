#include <windows.h>
#include <math.h>
#include <client/lib/CEGUI/standard/AnimationManager.h>
#include <client/lib/CEGUI/standard/Animation.h>
#include <client/lib/CEGUI/standard/FontManager.h>
#include <client/lib/CEGUI/standard/falagard/WidgetLookFeel.h>
#include <client/lib/CEGUI/standard/falagard/WidgetLookManager.h>
#include "client/lib/CEGUI/extend/falagard/actionbutton.h"

// Start of CEGUI namespace section
namespace CEGUI {

namespace extend {

namespace falagard {

  //////////////////////////////////////////////////////////////////////////
// Window type string
const utf8 ActionButton::WidgetTypeName[] = "Falagard/ActionButton";
// Event Strings
const String ActionButton::EventNamespace("Falagard/ActionButton");
const String ActionButton::EventDragStarted("DragStarted");
const String ActionButton::EventDragEnded("DragEnded");
const String ActionButton::EventDragPositionChanged("DragPositionChanged");
const String ActionButton::EventDragEnabledChanged("DragEnabledChanged");
const String ActionButton::EventDragThresholdChanged("DragThresholdChanged");
const String ActionButton::EventDragDropTargetChanged("DragDropTargetChanged");
const String ActionButton::EventDropItemEnters("DropItemEnters");
const String ActionButton::EventDropItemLeaves("DropItemLeaves");
const String ActionButton::EventDropItemDropped("DropItemDropped");
const String ActionButton::EventRBClicked((utf8*)"RBClicked");
const String ActionButton::EventItemReSet("ItemReSet");

ActionButtonProperties::Empty ActionButton::d_emptyProperty;
ActionButtonProperties::Checked ActionButton::d_checkedProperty;
ActionButtonProperties::Default ActionButton::d_defaultProperty;
ActionButtonProperties::Gloom  ActionButton::d_gloomProperty;
ActionButtonProperties::CornerChar ActionButton::d_cornerCharProperty;
ActionButtonProperties::DraggingEnabled ActionButton::d_dragEnabledProperty;
ActionButtonProperties::DragThreshold ActionButton::d_dragThresholdProperty;
ActionButtonProperties::DragAcceptName ActionButton::d_dragAcceptNameProperty;
ActionButtonProperties::FlashAnimation ActionButton::d_flashAnimationProperty;
ActionButtonProperties::BackImage ActionButton::d_BackImageProperty;
ActionButtonProperties::UseDefaultTooltip 
  ActionButton::d_UseDefaultTooltipProperty;
//construct function
ActionButton::ActionButton(const String& type, const String& name) :
  ButtonBase(type, name),
  d_empty(true),
  d_checked(false),
  d_default(false),
  //d_gloom(false),
  d_draggingEnabled(false),
  d_leftMouseDown(false),
  d_dragging(false),
  d_dragThreshold(4.0f),
  d_LogicData(0),
  d_ActiveButtonBase(LeftButtonBase),
  d_DragButtonBase(RightButtonBase) {
  addActionButtonProperties();
  d_animation1.d_animation = 0;
  d_animationFlash.d_animation = 0;
  setClippedByParent(false);
  d_gloom = false;
  d_percentageImg = 0;
  d_bFlash = false;
  d_isUseDefaultTooltip = false;
}

ActionButton::~ActionButton() {
  //do nothing
}

void ActionButton::initialise(void) {
  ButtonBase::initialise();
}

void ActionButton::addActionButtonProperties(void) {
  CEGUI_START_ADD_STATICPROPERTY(ActionButton)
  CEGUI_ADD_STATICPROPERTY(&d_emptyProperty);
  CEGUI_ADD_STATICPROPERTY(&d_checkedProperty);
  CEGUI_ADD_STATICPROPERTY(&d_defaultProperty);
  CEGUI_ADD_STATICPROPERTY(&d_gloomProperty);
  CEGUI_ADD_STATICPROPERTY(&d_cornerCharProperty);
  CEGUI_ADD_STATICPROPERTY(&d_dragEnabledProperty);
  CEGUI_ADD_STATICPROPERTY(&d_dragThresholdProperty);
  CEGUI_ADD_STATICPROPERTY(&d_dragAcceptNameProperty);
  CEGUI_ADD_STATICPROPERTY(&d_flashAnimationProperty);
  CEGUI_ADD_STATICPROPERTY(&d_BackImageProperty);
  CEGUI_ADD_STATICPROPERTY(&d_UseDefaultTooltipProperty);
  CEGUI_END_ADD_STATICPROPERTY
}

void ActionButton::setAnimation(const String& name, 
                              int time_total, 
                              float percent) {
  int time_now = (int)(System::getSingleton().getCurTimeElapsed()*1000.0f);
  int time_start = (int)(time_now - time_total*percent);
  if (NULL == AnimationManager::getSingletonPtr()) return;
  if (AnimationManager::getSingleton().isAnimationPresent(name)) {
    d_animation1.d_animation = 
      (Animation*)AnimationManager::getSingleton().getAnimation(name);
    d_animation1.d_time_start = time_start;
    d_animation1.d_time_total = time_total;
    d_animation1.d_currentFrame = 
      AnimationManager::getSingleton().getAnimation(name)->getFrame(0, time_total);
    if ((utf8*)"CoolDown" == name)
      d_CoolDown = true;
    else
      d_CoolDown = false;
    requestRedraw();
  }
}

void ActionButton::setPercentageImage(const String& animationName, 
                                      int cur, 
                                      int total) {
  const Animation* _Animation = 0;
  d_percentageImg = 0;
  //0.check para.
  if (abs(cur) > abs(total)) {
    requestRedraw();
    return;
  }

  //1.get animation.
  if (animationName.empty()) {
    _Animation = 
      AnimationManager::getSingleton().getAnimation((utf8*)"Percentage");
  }
  else {
    _Animation = AnimationManager::getSingleton().getAnimation(animationName);
  }

  //2.get img used to draw percentage.
  if(_Animation)
  {
    d_percentageImg = _Animation->getFrame(abs(cur), abs(total));
  }

  requestRedraw();
}

void ActionButton::cleanAnimation(void) {
  d_animation1.d_animation = 0;
  requestRedraw();
}

void ActionButton::cleanPercentageImage(void) {
  d_percentageImg = 0;
  requestRedraw();
}

void ActionButton::onParentSized(WindowEventArgs& e) {
  // base class handling.
  ButtonBase::onParentSized(e);
  d_BackImage.setSize(getUnclippedInnerRect().getSize());
  e.handled = true;
}

void ActionButton::onSized(WindowEventArgs& e) {
  ButtonBase::onSized(e);
  d_BackImage.setSize(getUnclippedInnerRect().getSize());
  e.handled = true;
}

void ActionButton::drawNormal(float z) {
  ButtonBase::drawNormal( z );
}

Tooltip* ActionButton::getTooltip(void) const {
  Tooltip* result = NULL;
  result = (d_empty || d_isUseDefaultTooltip) ? 
           System::getSingleton().getDefaultTooltip() 
           : 0;
  return result;
}

void ActionButton::drawSelf(float z) {
  if (d_needsRedraw) {
    d_renderCache.clearCachedImagery();
    d_needsRedraw = false;
    const StateImagery* imagery;
    // get WidgetLookFeel for the assigned look.
    const WidgetLookFeel& wlf = 
      WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
    if (wlf.isStateImageryPresent("BackgroundImage")) {
      imagery = &wlf.getStateImagery("BackgroundImage");
      // peform the rendering operation.
      imagery->render(*this);
    }
    // 画背景
    d_BackImage.draw(d_renderCache);
    //Empty
    if (isEmpty()) {
      if((isHovering() || isPushed()) && !isDisabled(true)) {
        drawHover(z);
      }
    }
    else {
      //Draw normal image
      drawNormal(z);

      //Draw percentage Img
      if (isPercentagePresent()) {
        drawPercentageImg(z);
      }

      //Notin Dragging
      if (d_dragging && !isGloom()) {
        drawPushed(z);
      }
      else {
        //Draw disable mask only when disabled
        if (isDisabled(true) || isGloom()) {
          drawDisabled(z);
          if (isPushed() || isChecked()) {
            drawPushed(z);
          }
          drawAnimation(z);
        }
        else {
          //If pushed or checked draw "Pushed" Layer
          if (isPushed() || isChecked()) {
            drawPushed(z);
          }

          //Draw "Hover" Layer
          if (isHovering() && !isChecked()) {
            drawHover(z);
          }

          drawAnimation(z);
          // If default
          if (isDefault()) {
            drawDefault(z);
          }
        }
        //Draw corner character
        drawCorner(z);
        drawFlash(z);
      }
    }
  }
  Window::drawSelf(z);
}

Rect ActionButton::getActionArea() {
  Rect rcOut;
  const WidgetLookFeel& wlf = 
    WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
  if (wlf.isNamedAreaDefined("ActionArea"))
    rcOut = wlf.getNamedArea("ActionArea").getArea().getPixelRect(*this);
  else
    rcOut= Rect(0, 0, getAbsoluteSize().d_width, getAbsoluteSize().d_height);
  return rcOut;
}

void ActionButton::drawFlash(float z) { //闪光效果
  if (!d_animationFlash.d_animation || !d_animationFlash.d_currentFrame) return;
  if (!d_bFlash) return;

  //Draw CornerChar
  ColourRect color(colour( 1.0f, 1.0f, 1.0f, 1.0f));
  color.setAlpha( d_animationFlash.d_alpha );
  d_renderCache.cacheImage(*(d_animationFlash.d_currentFrame),
                           getActionArea(), 
                           0, 
                           color);
}
void ActionButton::drawDefault(float z) {
  doButtonBaseRender("Defaulted");
}

void ActionButton::drawCorner(float z) {
  //Draw CornerChar
  ColourRect final_cols(colour(1.0f, 1.0f, 1.0f));
  //Top Left
  if (!d_CornerChar_TopLeft.d_Char.empty()) {
    d_renderCache.cacheText(
        this, 
        d_CornerChar_TopLeft.d_Char, 
        getFont(), 
        (TextFormatting)LeftAligned, 
        Rect(2, 2, getAbsoluteSize().d_width, getAbsoluteSize().d_height), 
        0.0f, 
        final_cols);
  }        
  //Top Right
  if (!d_CornerChar_TopRight.d_Char.empty()) {
    d_renderCache.cacheText(
        this, 
        d_CornerChar_TopRight.d_Char, 
        getFont(), 
        (TextFormatting)RightAligned, 
        Rect(0, 2, getAbsoluteSize().d_width - 2, getAbsoluteSize().d_height), 
        0.0f, 
        final_cols);
  }        
  //Bottom Left
  if (!d_CornerChar_BotLeft.d_Char.empty()) {
    //Get the font height
    float fFontHeight = getFont()->getFontHeight();
    d_renderCache.cacheText(
        this, 
        d_CornerChar_BotLeft.d_Char, 
        getFont(), 
        (TextFormatting)LeftAligned, 
        Rect(2, 
             getAbsoluteSize().d_height-fFontHeight - 2, 
             getAbsoluteSize().d_width, 
             getAbsoluteSize().d_height), 
        0.0f, 
        final_cols);
  }        
  //Bottom Right
  if(!d_CornerChar_BotRight.d_Char.empty()) {
    //Get the font height
    float fFontHeight = getFont()->getFontHeight();
    d_renderCache.cacheText(
        this, 
        d_CornerChar_BotRight.d_Char, 
        getFont(), 
        (TextFormatting)RightAligned, 
        Rect(0, 
             getAbsoluteSize().d_height-fFontHeight - 2, 
             getAbsoluteSize().d_width - 2, 
             getAbsoluteSize().d_height), 
        0.0f, 
        final_cols);
  }
}

void ActionButton::drawAnimation(float z) {
  if (!d_animation1.d_animation || !d_animation1.d_currentFrame) return;

  //Draw CornerChar
  ColourRect color(colour( 1.0f, 1.0f, 1.0f ));
  color.setAlpha(d_animation1.d_alpha);
  d_renderCache.cacheImage(*(d_animation1.d_currentFrame),
                           getActionArea(), 
                           0, 
                           color);
}

void ActionButton::drawPercentageImg(float z) {
  if (!d_percentageImg) return;
  //Draw CornerChar
  ColourRect color(colour(1.0f, 1.0f, 1));
  color.setAlpha(0.75f);
  d_renderCache.cacheImage(*d_percentageImg,
                           getActionArea(), 
                           0, 
                           color);
}

bool ActionButton::isDraggingThresholdExceeded(const Point& local_mouse) {
  // calculate amount mouse has moved.
  float  deltaX = fabsf(local_mouse.d_x - d_dragPoint.d_x);
  float  deltaY = fabsf(local_mouse.d_y - d_dragPoint.d_y);

  // see if mouse has moved far enough to start dragging operation
  return (deltaX > d_dragThreshold || deltaY > d_dragThreshold) ? true : false;
}

void ActionButton::updateAnimation(ANIMATE& animation) {
  if(!animation.d_animation) return;

  int time_now = (int)(System::getSingleton().getCurTimeElapsed()*1000.0f);

  const Image* pFrame = animation.d_animation->getFrame( time_now-animation.d_time_start, animation.d_time_total );
  if( pFrame )
  {
    animation.d_currentFrame = pFrame;
    animation.d_alpha = animation.d_animation->getFrameAlpha( time_now-animation.d_time_start, animation.d_time_total );
    requestRedraw();
  }
  else
  {
    if( m_bCoolDown ) // 如果是cooldown ，就开始播放特效动画
    {
      setAnimation( "CoolDownEnd", -1, 0 );
      animation.d_alpha = 0;
    }
  }
}
void ActionButton::updateAnimationFlash()
{
  if(!d_animationFlash.d_animation) return;

  int time_now = (int)(System::getSingleton().getCurTimeElapsed()*1000.0f);

  const Image* pFrame = d_animationFlash.d_animation->getFrame( time_now-d_animationFlash.d_time_start, d_animationFlash.d_time_total );
  d_animationFlash.d_currentFrame = pFrame;
  d_animationFlash.d_alpha = d_animationFlash.d_animation->getFrameAlpha( time_now-d_animationFlash.d_time_start, d_animationFlash.d_time_total );
  requestRedraw();

}
void ActionButton::updateSelf(float elapsed)
{
  updateAnimation(d_animation1);
  updateAnimationFlash();
}

void ActionButton::onMouseButtonBaseDown(MouseEventArgs& e)
{
  //      ButtonBase::onMouseButtonBaseDown(e);下面就是pushbutton中的部分
  // default processing
  Window::onMouseButtonBaseDown(e);

  if (e.button == LeftButtonBase || e.button == RightButtonBase)
  {
    if (captureInput())
    {
      d_pushed = true;
      updateInternalState(e.position);
      requestRedraw();
    }

    // event was handled by us.
    e.handled = true;
  }
  /////////////////////////////////////////////////////////
  if (e.button == LeftButtonBase && isDraggingEnabled())
  {
    if(!d_dragging)
    {
      // get position of mouse as co-ordinates local to this window.
      Point localPos = (getMetricsMode() == Relative) ? 
        relativeToAbsolute(screenToWindow(e.position)) :
      screenToWindow(e.position);

      // store drag point for possible sizing or moving operation.
      d_dragPoint = localPos;
      d_leftMouseDown = true;

    }

    e.handled = true;
  }

  if (e.button == RightButtonBase && isDraggingEnabled())
  {
    e.handled = true;
  }
}

void ActionButton::notifyDragingEnd(void)
{
  d_dragging = false;
  d_leftMouseDown = false;
  WindowEventArgs args(this);
  fireEvent(EventDragEnded, args, EventNamespace);

  requestRedraw();
}

void ActionButton::notifyDragDrop_Droped(ActionButton* pBtn)
{

}

void ActionButton::onMouseButtonBaseUp(MouseEventArgs& e)
{
  //  ButtonBase::onMouseButtonBaseUp(e);下面就是pushbutton中的部分
  if ((e.button == LeftButtonBase) && isPushed())
  {
    Window* sheet = System::getSingleton().getGUISheet();

    if (sheet != NULL)
    {
      // if mouse was released over this widget
      if (this == sheet->getChildAtPosition(e.position))
      {
        // fire event
        WindowEventArgs args(this);
        onClicked(args);
      }

    }

    e.handled = true;
  }

  if(e.button == RightButtonBase)
  {
    Window* sheet = System::getSingleton().getGUISheet();

    if (sheet != NULL)
    {
      // if mouse was released over this widget
      if (this == sheet->getChildAtPosition(e.position))
      {
        // fire event
        WindowEventArgs args(this);
        onRBClicked(args);
      }

    }

  }

  // default handling
  //    ButtonBase::onMouseButtonBaseUp(e);下面就是buttonbase中的部分
  Window::onMouseButtonBaseUp(e);

  if (e.button == LeftButtonBase || e.button == RightButtonBase)
  {
    releaseInput();

    // event was handled by us.
    e.handled = true;
  }

  d_leftMouseDown = false;
}

void ActionButton::FirReSet(void)
{

  WindowEventArgs args(this);
  fireEvent(EventItemReSet, args, EventNamespace);
}
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
void ActionButton::onMouseMove(MouseEventArgs& e)
{
ButtonBase::onMouseMove(e);

  if(isDraggingEnabled() && !d_dragging && !isEmpty())
  {
    // get position of mouse as co-ordinates local to this window.
    Point localMousePos = (getMetricsMode() == Relative) ? 
      relativeToAbsolute(screenToWindow(e.position)) :
    screenToWindow(e.position);

    // if mouse button is down (but we're not yet being dragged)
    if (d_leftMouseDown)
    {
      if (isDraggingThresholdExceeded(localMousePos))
      {
        // Trigger the event
        WindowEventArgs args(this);
        d_dragging = true;
        releaseInput();

        fireEvent(EventDragStarted, e, EventNamespace);
      }
    }
  }
}

void ActionButton::onClicked(WindowEventArgs& e)
{
  if(d_dragging) return;

ButtonBase::onClicked(e);
}

void ActionButton::onRBClicked(WindowEventArgs& e)
{
  if(d_dragging) return;

  fireEvent(EventRBClicked, e, EventNamespace);
}

void ActionButton::subscribeDragDropStartedEvent(Event::Subscriber subscriber)
{
  subscribeEvent(EventDragStarted, subscriber);
}

void ActionButton::subscribeMouseEnterEvent(Event::Subscriber subscriber)
{
  subscribeEvent(EventMouseEnters, subscriber);
}

void ActionButton::subscribeMouseLeaveEvent(Event::Subscriber subscriber)
{

  subscribeEvent(EventMouseLeaves, subscriber);
}

String32 ActionButton::getCornerChar(int nPos) const
{
  switch(nPos)
  {
  case 0: return d_CornerChar_TopLeft.d_Char;
  case 1: return d_CornerChar_TopRight.d_Char;
  case 2: return d_CornerChar_BotLeft.d_Char;
  case 3: return d_CornerChar_BotRight.d_Char;
  default: return "";
  }
}

void ActionButton::setCornerChar(int nPos, const String32& strChar)
{
  String32 strCharSafe="  ";
  if(strChar.size() > 3)
  {
    strCharSafe += strChar.substr(0, 3);
  }
  else strCharSafe += strChar;
  strCharSafe[0] = 0XFBFFFFFF;
  strCharSafe[1] = 0XFC010101;

  switch(nPos)
  {
  case 0: d_CornerChar_TopLeft.d_Char    = strCharSafe; break;
  case 1: d_CornerChar_TopRight.d_Char  = strCharSafe; break;
  case 2: d_CornerChar_BotLeft.d_Char    = strCharSafe; break;
  case 3: d_CornerChar_BotRight.d_Char  = strCharSafe; break;
  default: break;
  }

  requestRedraw();
}

void ActionButton::prepareBigchar(void)
{
  Window::prepareBigchar();

  ((FontBase*)getFont())->prepareString(d_CornerChar_TopLeft.d_Char);
  ((FontBase*)getFont())->prepareString(d_CornerChar_TopRight.d_Char);
  ((FontBase*)getFont())->prepareString(d_CornerChar_BotLeft.d_Char);
  ((FontBase*)getFont())->prepareString(d_CornerChar_BotRight.d_Char);
}
void ActionButton::setFlashAnimation( const String& strAnimationName )
{
  if( AnimationManager::getSingletonPtr() == NULL )
    return;
  int time_now = (int)(System::getSingleton().getCurTimeElapsed()*1000.0f);
  int time_start = (int)(time_now );

  if(AnimationManager::getSingleton().isAnimationPresent(strAnimationName))
  {
    d_animationFlash.d_animation = ( Animation*)AnimationManager::getSingleton().getAnimation(strAnimationName);
    d_animationFlash.d_time_start = time_start;
    d_animationFlash.d_time_total = d_animationFlash.d_animation->getTotalTime();
    d_animationFlash.d_currentFrame = d_animationFlash.d_animation->getFrame( 0 );
    requestRedraw();
  }

}
void ActionButton::setBackImage( const Image* pImage )
{
  d_BackImage.setImage(pImage);
  d_BackImage.setHorzFormatting(RenderableImage::HorzStretched);
  d_BackImage.setVertFormatting(RenderableImage::VertStretched);
  d_BackImage.setSize(getUnclippedInnerRect().getSize());
  requestRedraw();
}


//////////////////////////////////////////////////////////////////////////
/*************************************************************************

Factory Methods

*************************************************************************/
//////////////////////////////////////////////////////////////////////////
Window* ActionButtonFactory::createWindow(const String& name)
{
  return new ActionButton(d_type, name);
}

void ActionButtonFactory::destroyWindow(Window* window)
{
  delete window;
}

} //namespace falagard

} //namespace extend

} //namespace CEGUI
