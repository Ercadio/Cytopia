#ifndef I_LAYOUT_HXX
#define I_LAYOUT_HXX

#include <vector>

#include "iView.hxx"
#include "iWidget.hxx"
#include "BoxSizing.hxx"

class iLayout : public iView
{

  std::vector<iWidgetPtr> m_Elements;
  PaddingConfiguration m_PaddingConfiguration;

public:
  
  class ElementRange
  {
  public:
    using iterator = std::vector<iWidgetPtr>::iterator;
    ElementRange(iLayout &);
    iterator begin();
    iterator end();
  private:
    iterator m_Begin;
    iterator m_End;
  };


  /**
   * @returns the PaddingConfiguration of the iLayout
   * @details the PaddingConfiguration only contains pixel values
   */
  const PaddingConfiguration & getPadding() const;

  virtual void draw(iRendererPtr &) const noexcept final;
  
  void setup() noexcept;

  virtual ~iLayout() = 0;

protected:

  /**
   * @brief Adds a iWidget to the iLayout
   * @param iWidgetPtr the iWidget to add
   */
  void addElement(iWidgetPtr &&);

  /**
   * @brief Sets the PaddingConfiguration of a iLayout
   */
  void setPadding(PaddingConfiguration &&) noexcept;

  ElementRange elements() noexcept;

  /**
   * @brief compute the boundaries of all iViews
   */
  virtual void computeBoundaries() noexcept = 0;

};

#endif // I_LAYOUT_HXX
