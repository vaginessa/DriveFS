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
 * Reply.h
 *
 * A reply to a comment on a file.
 */

#ifndef Reply_H_
#define Reply_H_


#include "ModelBase.h"

#include <cpprest/details/basic_types.h>
#include "User.h"

namespace io {
namespace swagger {
namespace client {
namespace model {

/// <summary>
/// A reply to a comment on a file.
/// </summary>
class  Reply
    : public ModelBase
{
public:
    Reply();
    virtual ~Reply();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    void fromJson(web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    void fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// Reply members

    /// <summary>
    /// The action the reply performed to the parent comment. Valid values are:   - resolve  - reopen
    /// </summary>
    utility::string_t getAction() const;
    bool actionIsSet() const;
    void unsetAction();
    void setAction(utility::string_t value);
    /// <summary>
    /// The user who created the reply.
    /// </summary>
    std::shared_ptr<User> getAuthor() const;
    bool authorIsSet() const;
    void unsetAuthor();
    void setAuthor(std::shared_ptr<User> value);
    /// <summary>
    /// The plain text content of the reply. This field is used for setting the content, while htmlContent should be displayed. This is required on creates if no action is specified.
    /// </summary>
    utility::string_t getContent() const;
    bool contentIsSet() const;
    void unsetContent();
    void setContent(utility::string_t value);
    /// <summary>
    /// The time at which the reply was created (RFC 3339 date-time).
    /// </summary>
    utility::datetime getCreatedTime() const;
    bool createdTimeIsSet() const;
    void unsetCreatedTime();
    void setCreatedTime(utility::datetime value);
    /// <summary>
    /// Whether the reply has been deleted. A deleted reply has no content.
    /// </summary>
    bool getDeleted() const;
    bool deletedIsSet() const;
    void unsetDeleted();
    void setDeleted(bool value);
    /// <summary>
    /// The content of the reply with HTML formatting.
    /// </summary>
    utility::string_t getHtmlContent() const;
    bool htmlContentIsSet() const;
    void unsetHtmlContent();
    void setHtmlContent(utility::string_t value);
    /// <summary>
    /// The ID of the reply.
    /// </summary>
    utility::string_t getId() const;
    bool idIsSet() const;
    void unsetId();
    void setId(utility::string_t value);
    /// <summary>
    /// Identifies what kind of resource this is. Value: the fixed string \&quot;drive#reply\&quot;.
    /// </summary>
    utility::string_t getKind() const;
    bool kindIsSet() const;
    void unsetKind();
    void setKind(utility::string_t value);
    /// <summary>
    /// The last time the reply was modified (RFC 3339 date-time).
    /// </summary>
    utility::datetime getModifiedTime() const;
    bool modifiedTimeIsSet() const;
    void unsetModifiedTime();
    void setModifiedTime(utility::datetime value);

protected:
    utility::string_t m_Action;
    bool m_ActionIsSet;
    std::shared_ptr<User> m_Author;
    bool m_AuthorIsSet;
    utility::string_t m_Content;
    bool m_ContentIsSet;
    utility::datetime m_CreatedTime;
    bool m_CreatedTimeIsSet;
    bool m_Deleted;
    bool m_DeletedIsSet;
    utility::string_t m_HtmlContent;
    bool m_HtmlContentIsSet;
    utility::string_t m_Id;
    bool m_IdIsSet;
    utility::string_t m_Kind;
    bool m_KindIsSet;
    utility::datetime m_ModifiedTime;
    bool m_ModifiedTimeIsSet;
};

}
}
}
}

#endif /* Reply_H_ */