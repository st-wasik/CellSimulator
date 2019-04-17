#pragma once
struct RegexPattern
{
	static constexpr const char * const Word = "[a-zA-Z_]+";
	static constexpr const char * const Double = "[0-9]+\\.?[0-9]*";
	static constexpr const char * const Vector = "\\{[0-9]+\\.?[0-9]*(, [0-9]+\\.?[0-9]*)*\\}";
	static constexpr const char * const Vector2 = "\\{[0-9]+\\.?[0-9]*(, [0-9]+\\.?[0-9]*){1}\\}";
	static constexpr const char * const Vector4 = "\\{[0-9]+\\.?[0-9]*(, [0-9]+\\.?[0-9]*){3}\\}";
};