/**
 * Drive
 * Manages files in Drive including uploading, downloading, searching, detecting changes, and updating sharing permissions.
 *
 * OpenAPI spec version: v3
 * 
 *
 * NOTE: This class is auto generated by the swagger code generator 2.2.3.
 * https://github.com/swagger-api/swagger-codegen.git
 * Do not edit the class manually.
 */

/*
 * Permission_teamDrivePermissionDetails.h
 *
 * 
 */

#ifndef Permission_teamDrivePermissionDetails_H_
#define Permission_teamDrivePermissionDetails_H_


#include "ModelBase.h"

#include <cpprest/details/basic_types.h>

namespace io {
namespace swagger {
namespace client {
namespace model {

/// <summary>
/// 
/// </summary>
class  Permission_teamDrivePermissionDetails
    : public ModelBase
{
public:
    Permission_teamDrivePermissionDetails();
    virtual ~Permission_teamDrivePermissionDetails();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    void fromJson(web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    void fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// Permission_teamDrivePermissionDetails members

    /// <summary>
    /// Whether this permission is inherited. This field is always populated. This is an output-only field.
    /// </summary>
    bool getInherited() const;
    bool inheritedIsSet() const;
    void unsetInherited();
    void setInherited(bool value);
    /// <summary>
    /// The ID of the item from which this permission is inherited. This is an output-only field and is only populated for members of the Team Drive.
    /// </summary>
    utility::string_t getInheritedFrom() const;
    bool inheritedFromIsSet() const;
    void unsetInheritedFrom();
    void setInheritedFrom(utility::string_t value);
    /// <summary>
    /// The primary role for this user. While new values may be added in the future, the following are currently possible:   - organizer  - writer  - commenter  - reader
    /// </summary>
    utility::string_t getRole() const;
    bool roleIsSet() const;
    void unsetRole();
    void setRole(utility::string_t value);
    /// <summary>
    /// The Team Drive permission type for this user. While new values may be added in future, the following are currently possible:   - file  - member
    /// </summary>
    utility::string_t getTeamDrivePermissionType() const;
    bool teamDrivePermissionTypeIsSet() const;
    void unsetTeamDrivePermissionType();
    void setTeamDrivePermissionType(utility::string_t value);

protected:
    bool m_Inherited;
    bool m_InheritedIsSet;
    utility::string_t m_InheritedFrom;
    bool m_InheritedFromIsSet;
    utility::string_t m_Role;
    bool m_RoleIsSet;
    utility::string_t m_TeamDrivePermissionType;
    bool m_TeamDrivePermissionTypeIsSet;
};

}
}
}
}

#endif /* Permission_teamDrivePermissionDetails_H_ */