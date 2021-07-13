#include "include/GoodEatsErrors.hpp"

Error::Error(std::string& moreInfo, std::string basicInfo) : moreInfo_(std::move(moreInfo)), basicInfo_(std::move(basicInfo)) { }

std::string Error::moreInfo() const
{
	return moreInfo_;
}

char const* Error::what() const noexcept
{
	return basicInfo_.c_str();
}

NotFoundError::NotFoundError(std::string moreInfo) : Error(moreInfo, "Not Found") { }

BadRequest::BadRequest(std::string moreInfo) : Error(moreInfo, "Bad Request") { }

PermissionDenied::PermissionDenied(std::string moreInfo) : Error(moreInfo, "Permission Denied") { }
