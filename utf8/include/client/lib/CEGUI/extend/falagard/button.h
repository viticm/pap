/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id button.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-24 10:39:18
 * @uses cegui extend falagard button class.
 */
#ifndef PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_BUTTON_H_
#define PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_BUTTON_H_

// Start of CEGUI namespace section
namespace CEGUI
{
class Animate;
/*!
\brief
Button class for the FalagardBase module.

This class requires LookNFeel to be assigned.  The LookNFeel should provide the following:

States (missing states will default to 'Normal'):
- Normal    - Rendering for when the button is neither pushed or has the mouse hovering over it.
- Hover     - Rendering for then the button has the mouse hovering over it.
- Pushed    - Rendering for when the button is pushed.
- Disabled  - Rendering for when the button is disabled.
*/
namespace FalagardButtonProperties
{
	class Flash : public Property
	{
	public:
		Flash() : Property(
			"Flash",
			"Property to get/set empty status.",
			"0")
		{}

		String   get(const PropertyReceiver* receiver) const;
		void   set(PropertyReceiver* receiver, const String& value);
	};

	class BtnAnimation : public Property
	{
	public:
		BtnAnimation() : Property(
			"BtnAnimation",
			"Property to get/set empty status.",
			"")
		{}

		String   get(const PropertyReceiver* receiver) const;
		void   set(PropertyReceiver* receiver, const String& value);
	};
};

class FALAGARDBASE_API FalagardButton : public PushButton
{
public:
	static const utf8   WidgetTypeName[];       //!< type name for this widget.
	static FalagardButtonProperties::Flash		d_flashProperty;
	static FalagardButtonProperties::BtnAnimation		d_btnAnimationProperty;
	/*!
	\brief
	Constructor
	*/
	FalagardButton(const String& type, const String& name);

	/*!
	\brief
	Destructor
	*/
	~FalagardButton();

	// overridden from ButtonBase.
	void drawSelf(float z);

	// implementation of abstract methods in ButtonBase
	void drawNormal(float z);
	void drawHover(float z);
	void drawPushed(float z);
	void drawDisabled(float z);
	void			setFlash( int nMode ){d_nFlash=nMode;};
	const int		getFlash() const{return d_nFlash;};
	virtual Size getRenderSize();
	virtual	void updateSelf(float elapsed);
protected:
	void doButtonRender(const String& state);


protected:
	int					d_nFlash;	 //0:ÉÁ£¬1²»ÉÁ
	float				d_ReturnTimer;
	bool				d_bflsh;
protected:
	struct ANIMATE
	{
		Animate*		d_animate;
		int				d_time_start;
		int				d_time_total;
		const Image*	d_currentFrame;
		float			d_alpha;
		ANIMATE(){
			d_animate = NULL;
			d_time_start = 0;
			d_time_total = 0;
			d_currentFrame = 0;
			d_alpha			= 0;

		};
	};

	ANIMATE			d_btnAnimate;
	bool			d_enableAnimate;

	void updateAnimate(void);
	void drawAnimate(float z);
public:
	void enableAnimate(bool yes);

	void setBtnAnimation(const String& val);
};

/*!
\brief
WindowFactory for FalagardButton type Window objects.
*/
class FALAGARDBASE_API FalagardButtonFactory : public WindowFactory
{
public:
	FalagardButtonFactory(void) : WindowFactory(FalagardButton::WidgetTypeName) { }
	~FalagardButtonFactory(void){}
	Window* createWindow(const String& name);
	void destroyWindow(Window* window);
};

} // End of  CEGUI namespace section

#endif //PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_BUTTON_H_
