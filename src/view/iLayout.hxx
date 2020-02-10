#ifndef I_LAYOUT_HXX
#define I_LAYOUT_HXX

#include <vector>

#include "iView.hxx"
#include "iViewElement.hxx"
#include "BoxSizing.hxx"

class iLayout : public virtual iView
{

  std::vector<iViewElementPtr> m_Elements;
  PaddingConfiguration m_PaddingConfiguration;
  Rectangle m_Bounds;

public:
  
  class ElementRange
  {
  public:
    using iterator = std::vector<iViewElementPtr>::iterator;
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

  iLayout(Rectangle &&);
  virtual ~iLayout() = 0;

protected:

  /**
   * @brief Adds a iViewElement to the iLayout
   * @param iViewElementPtr the iViewElement to add
   */
  void addElement(iViewElementPtr &&);

  /**
   * @brief Sets the PaddingConfiguration of a iLayout
   */
  void setPadding(PaddingConfiguration &&) noexcept;

  ElementRange elements() noexcept;

  /**
   * @brief compute the boundaries of all iViews
   */
  virtual void computeBoundaries() noexcept = 0;

  const Rectangle & getBounds() const noexcept final;

private:
  void setBounds(Rectangle &&) noexcept final;
};

#endif // I_LAYOUT_HXX
