#pragma once
class Utils
{
public:
	// https://cplusplus.com/forum/general/113069/
	template <typename T>
	static constexpr T remap(T value, T istart, T istop, T ostart, T ostop) {
		if (istop == istart) return 0;
		return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
	}
};

