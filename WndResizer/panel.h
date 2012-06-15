#ifndef _panel_h_
#define _panel_h_

#include <list>

class CPanel
{
private:
	RECT m_rect;
	CPanel * m_pParent;
	std::list<CPanel *> m_children;

public:
	CPanel(CPanel * parent = NULL);
	CPanel(const RECT& rect, CPanel * parent = NULL);
	virtual ~CPanel();
private:
	CPanel(const CPanel& rhs);
	CPanel& operator=(const CPanel& rhs);

public:
	// Get operations
	inline RECT& GetRect() { return m_rect; }
	inline const RECT& GetRect() const { return m_rect; }

	inline CPanel * GetParent() { return m_pParent; }
	inline const CPanel * GetParent() const { return m_pParent; }

	inline void SetParent(CPanel * panel) { m_pParent = panel; }

	inline const std::list<CPanel *>& GetChildren() { return m_children; }
	inline const std::list<const CPanel *> GetChildren() const { 
		return std::list<const CPanel *>(m_children.begin(), m_children.end()); 
	}

	inline void AddChild(CPanel * panel) { panel->SetParent(this); m_children.push_back(panel); }

	// Set operations
	void SetRect(const RECT& rect);
	void SetRect(int left, int top, int right, int bottom);

	virtual void OnResize(int l_offset, int t_offset, int r_offset, int b_offset);
	virtual void OnMove(int x, int y);
	virtual void OnPaint();
};

inline int GetRectWidth(const RECT& r) { return r.right - r.left; }
inline int GetRectHeight(const RECT& r) { return r.bottom - r.top; }

#endif