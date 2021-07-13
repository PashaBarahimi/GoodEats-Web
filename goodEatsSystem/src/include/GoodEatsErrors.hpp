#ifndef GOOD_EATS_ERRORS_HPP
#define GOOD_EATS_ERRORS_HPP

#include <string>
#include <exception>

class Error : public std::exception
{
public:
	Error(std::string& moreInfo, std::string basicInfo);
	std::string moreInfo() const;
	char const* what() const noexcept override;
protected:
	std::string moreInfo_;
	std::string basicInfo_;
};

class NotFoundError : public Error
{
public:
	NotFoundError(std::string moreInfo);
};

class BadRequest : public Error
{
public:
	BadRequest(std::string moreInfo);
};

class PermissionDenied : public Error
{
public:
	PermissionDenied(std::string moreInfo);
};
#endif