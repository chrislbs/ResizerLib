#ifdef _AFXDLL

#include "wndpanel.h"
#include <iterator>

template<typename InputIterator, typename OutputIterator>
void CreateWndPanels(InputIterator begin, InputIterator end, OutputIterator out, UINT anchor = 0)
{
	_CreateWndPanels(
		begin, end, out, anchor,
		typename std::iterator_traits<InputIterator>::iterator_category(),
		typename std::iterator_traits<InputIterator>::value_type(),
		typename std::iterator_traits<OutputIterator>::iterator_category());
}

template<typename InputIterator, typename OutputIterator>
void _CreateWndPanels(
	InputIterator begin,
	InputIterator end,
	OutputIterator out,
	UINT anchor,
	typename std::input_iterator_tag,
	typename CWnd,
	typename std::output_iterator_tag)
{
	while(begin != end)
	{
		*out = new CWndPanel(begin->GetSafeHwnd(), anchor);
		++out;
		++begin;
	}
}

template<typename InputIterator>
void SetPanelsParent(CPanel * parent, InputIterator begin, InputIterator end)
{
	_SetPanelsParent(
		parent, begin, end,
		typename std::iterator_traits<InputIterator>::iterator_category(),
		typename std::iterator_traits<InputIterator>::value_type());
}

template<typename InputIterator>
void _SetPanelsParent(
	CPanel * parent,
	InputIterator begin, 
	InputIterator end,
	typename std::input_iterator_tag,
	typename CPanel *)
{
	while(begin != end)
	{
		parent->AddChild(*begin);
		++begin;
	}
}

#endif // is def _AFXDLL