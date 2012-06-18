#ifdef _AFXDLL

#include "wndpanel.h"
#include <iterator>

template<typename InputIterator, typename OutputIterator>
void CreateWndPanels(InputIterator begin, InputIterator end, OutputIterator out, UINT anchor = 0)
{
	_CreateWndPanels(begin, end, out, anchor);
}

// this is the coolest magic i've ever seen
template<typename InputIterator, typename OutputIterator>
typename std::enable_if<
	std::is_base_of<CWnd, typename std::iterator_traits<InputIterator>::value_type>::value &&
	std::is_base_of<std::input_iterator_tag, typename std::iterator_traits<InputIterator>::iterator_category>::value &&
	std::is_base_of<std::output_iterator_tag, typename std::iterator_traits<OutputIterator>::iterator_category>::value
>::type
_CreateWndPanels(InputIterator begin, InputIterator end, OutputIterator out, UINT anchor)
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
	_SetPanelsParent(parent, begin, end);
}

// more template magic
template<typename InputIterator>
typename std::enable_if<
	std::is_convertible<typename std::iterator_traits<InputIterator>::value_type, CPanel *>::value &&
	std::is_base_of<std::input_iterator_tag, typename std::iterator_traits<InputIterator>::iterator_category>::value
>::type
_SetPanelsParent(
	CPanel * parent,
	InputIterator begin, 
	InputIterator end)
{
	while(begin != end)
	{
		parent->AddChild(*begin);
		++begin;
	}
}

#endif // is def _AFXDLL