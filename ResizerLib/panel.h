#ifndef _panel_h_
#define _panel_h_

#include <list>
#include <Windows.h>

namespace df {

const int ANCHOR_LEFT	= 1;
const int ANCHOR_TOP	= 2;
const int ANCHOR_RIGHT	= 4;
const int ANCHOR_BOTTOM	= 8;
const int ANCHOR_VERT	= ANCHOR_TOP | ANCHOR_BOTTOM;
const int ANCHOR_HORZ	= ANCHOR_LEFT | ANCHOR_RIGHT;
const int ANCHOR_ALL	= ANCHOR_VERT | ANCHOR_HORZ;
const RECT EMPTY_RECT = {0};

class CPanel
{
public:
	typedef RECT OFFSET;

private:
	RECT m_rect;
	OFFSET m_offset;
	UINT m_anchor;
	std::list<CPanel *> m_children;

public:
	CPanel(const RECT& rect = EMPTY_RECT, UINT anchor = 0);
protected:
	virtual ~CPanel();
private:
	CPanel(const CPanel& rhs);
	CPanel& operator=(const CPanel& rhs);

public:
	inline void SetRect(const RECT& rect) { memcpy_s(&m_rect, sizeof(RECT), &rect, sizeof(RECT)); }
	inline const RECT& GetRect() const { return m_rect; }

	inline void SetOffset(const OFFSET& off) { memcpy_s(&m_offset, sizeof(OFFSET), &off, sizeof(OFFSET)); }
	inline const OFFSET& GetOffset() const { return m_offset; }

	inline UINT GetAnchor() const { return m_anchor; }
	inline void SetAnchor(UINT anchor) { m_anchor = anchor; }

	// implement iterators
	inline std::list<CPanel*>& GetChildren() { return m_children; }
	inline const std::list<CPanel *>& GetChildren() const { return m_children; }

	void AddChild(CPanel * panel);

	virtual void OnDestroy();
};

inline int GetRectWidth(const RECT& r) { return r.right - r.left; }
inline int GetRectHeight(const RECT& r) { return r.bottom - r.top; }

} // end namespace df

#endif