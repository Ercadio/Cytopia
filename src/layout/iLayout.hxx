#ifndef I_LAYOUT_HXX
#define I_LAYOUT_HXX

#include <vector>

#include "../util/Range.hxx"
#include "../view/iView.hxx"
#include "../view/iViewElement.hxx"
#include "../view/BoxSizing.hxx"
#include "../controller/iController.hxx"

class iLayout : public virtual iView
{

  std::vector<iControllerPtr> m_Controllers;
  using ElementList = std::vector<iViewPtr>;
  ElementList m_Elements;
  PaddingConfiguration m_PaddingConfiguration;
  Rectangle m_Bounds;
  
public:

  /**
   * @returns the PaddingConfiguration of the iLayout
   * @details the PaddingConfiguration only contains pixel values
   */
  const PaddingConfiguration & getPadding() const;

  virtual void draw(iRenderer &) const noexcept override;

  iLayout(Rectangle && = Rectangle{0, 0, 0, 0});
  virtual ~iLayout() = 0;
  
  void setup() noexcept override;
  void bindHandlers(class GameService & context) noexcept override;

protected:

  /**
   * @brief Adds a iView to the iLayout
   * @param iViewPtr the iView to add
   */
  iViewPtr addElement(iViewPtr);

  /**
   * @brief Adds a new controller to the iLayout
   * @param iControllerPtr the iController to add
   * @tparam ControllerType the type of the controller
   * @tparam Args the arguments to construct the controller
   */
  template <typename ControllerType, typename... Args>
  ControllerType & createController(Args &&... args);

  /**
   * @brief Sets the PaddingConfiguration of a iLayout
   */
  void setPadding(PaddingConfiguration &&) noexcept;

  Range<typename ElementList::iterator> elements() noexcept;
  Range<typename ElementList::const_iterator> elements() const noexcept;

  /**
   * @brief compute the boundaries of all iViews
   */
  virtual void computeBoundaries() noexcept = 0;

  const Rectangle & getBounds() const noexcept final;

private:
  void setBounds(Rectangle &&) noexcept final;
};

#include "iLayout.inl.hxx"

#endif // I_LAYOUT_HXX
