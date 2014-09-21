#ifndef INSPIRIT_IGAMESCREEN_HPP
#define INSPIRIT_IGAMESCREEN_HPP
namespace inspirit
{
class IGameScreen
{
public:
  // Called when the screen is made current
  virtual void Init() { }
  // Called only once on a screen during each existence
  // call the base version at the top of the implementation
  virtual void Load();
  // ----------------------------
  // Must implement
  // ---------------
  virtual void Render() const = 0;
  virtual void Update(double time) const = 0;
  // ------------------------
  virtual void OnKeyPress(int key, int action) const { }
  virtual void OnMouseClick(int btn, int actn) const { }
private:
  friend class Engine;
  bool _is_loaded = false;
};
};
#endif // INSPIRIT_IGAMESCREEN_HPP
