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
 * RevisionsApi.h
 *
 * 
 */

#ifndef RevisionsApi_H_
#define RevisionsApi_H_


#include "ApiClient.h"

#include "Revision.h"
#include "RevisionList.h"
#include <cpprest/details/basic_types.h>

namespace io {
namespace swagger {
namespace client {
namespace api {

using namespace io::swagger::client::model;

class  RevisionsApi
{
public:
    RevisionsApi( std::shared_ptr<ApiClient> apiClient );
    virtual ~RevisionsApi();
    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// Permanently deletes a revision. This method is only applicable to files with binary content in Drive.
    /// </remarks>
    /// <param name="fileId">The ID of the file.</param>/// <param name="revisionId">The ID of the revision.</param>/// <param name="alt">Data format for the response. (optional, default to json)</param>/// <param name="fields">Selector specifying which fields to include in a partial response. (optional)</param>/// <param name="key">API key. Your API key identifies your project and provides you with API access, quota, and reports. Required unless you provide an OAuth 2.0 token. (optional)</param>/// <param name="oauthToken">OAuth 2.0 token for the current user. (optional)</param>/// <param name="prettyPrint">Returns response with indentations and line breaks. (optional, default to true)</param>/// <param name="quotaUser">Available to use for quota purposes for server-side applications. Can be any arbitrary string assigned to a user, but should not exceed 40 characters. Overrides userIp if both are provided. (optional)</param>/// <param name="userIp">IP address of the site where the request originates. Use this if you want to enforce per-user limits. (optional)</param>
    pplx::task<void> delete_(utility::string_t fileId, utility::string_t revisionId, utility::string_t alt, utility::string_t fields, utility::string_t key, utility::string_t oauthToken, bool prettyPrint, utility::string_t quotaUser, utility::string_t userIp);
    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// Gets a revision&#39;s metadata or content by ID.
    /// </remarks>
    /// <param name="fileId">The ID of the file.</param>/// <param name="revisionId">The ID of the revision.</param>/// <param name="alt">Data format for the response. (optional, default to json)</param>/// <param name="fields">Selector specifying which fields to include in a partial response. (optional)</param>/// <param name="key">API key. Your API key identifies your project and provides you with API access, quota, and reports. Required unless you provide an OAuth 2.0 token. (optional)</param>/// <param name="oauthToken">OAuth 2.0 token for the current user. (optional)</param>/// <param name="prettyPrint">Returns response with indentations and line breaks. (optional, default to true)</param>/// <param name="quotaUser">Available to use for quota purposes for server-side applications. Can be any arbitrary string assigned to a user, but should not exceed 40 characters. Overrides userIp if both are provided. (optional)</param>/// <param name="userIp">IP address of the site where the request originates. Use this if you want to enforce per-user limits. (optional)</param>/// <param name="acknowledgeAbuse">Whether the user is acknowledging the risk of downloading known malware or other abusive files. This is only applicable when alt&#x3D;media. (optional, default to false)</param>
    pplx::task<std::shared_ptr<Revision>> get(utility::string_t fileId, utility::string_t revisionId, utility::string_t alt, utility::string_t fields, utility::string_t key, utility::string_t oauthToken, bool prettyPrint, utility::string_t quotaUser, utility::string_t userIp, bool acknowledgeAbuse);
    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// Lists a file&#39;s revisions.
    /// </remarks>
    /// <param name="fileId">The ID of the file.</param>/// <param name="alt">Data format for the response. (optional, default to json)</param>/// <param name="fields">Selector specifying which fields to include in a partial response. (optional)</param>/// <param name="key">API key. Your API key identifies your project and provides you with API access, quota, and reports. Required unless you provide an OAuth 2.0 token. (optional)</param>/// <param name="oauthToken">OAuth 2.0 token for the current user. (optional)</param>/// <param name="prettyPrint">Returns response with indentations and line breaks. (optional, default to true)</param>/// <param name="quotaUser">Available to use for quota purposes for server-side applications. Can be any arbitrary string assigned to a user, but should not exceed 40 characters. Overrides userIp if both are provided. (optional)</param>/// <param name="userIp">IP address of the site where the request originates. Use this if you want to enforce per-user limits. (optional)</param>/// <param name="pageSize">The maximum number of revisions to return per page. (optional, default to 200)</param>/// <param name="pageToken">The token for continuing a previous list request on the next page. This should be set to the value of &#39;nextPageToken&#39; from the previous response. (optional)</param>
    pplx::task<std::shared_ptr<RevisionList>> list(utility::string_t fileId, utility::string_t alt, utility::string_t fields, utility::string_t key, utility::string_t oauthToken, bool prettyPrint, utility::string_t quotaUser, utility::string_t userIp, int32_t pageSize, utility::string_t pageToken);
    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// Updates a revision with patch semantics.
    /// </remarks>
    /// <param name="fileId">The ID of the file.</param>/// <param name="revisionId">The ID of the revision.</param>/// <param name="alt">Data format for the response. (optional, default to json)</param>/// <param name="fields">Selector specifying which fields to include in a partial response. (optional)</param>/// <param name="key">API key. Your API key identifies your project and provides you with API access, quota, and reports. Required unless you provide an OAuth 2.0 token. (optional)</param>/// <param name="oauthToken">OAuth 2.0 token for the current user. (optional)</param>/// <param name="prettyPrint">Returns response with indentations and line breaks. (optional, default to true)</param>/// <param name="quotaUser">Available to use for quota purposes for server-side applications. Can be any arbitrary string assigned to a user, but should not exceed 40 characters. Overrides userIp if both are provided. (optional)</param>/// <param name="userIp">IP address of the site where the request originates. Use this if you want to enforce per-user limits. (optional)</param>/// <param name="body"> (optional)</param>
    pplx::task<std::shared_ptr<Revision>> update(utility::string_t fileId, utility::string_t revisionId, utility::string_t alt, utility::string_t fields, utility::string_t key, utility::string_t oauthToken, bool prettyPrint, utility::string_t quotaUser, utility::string_t userIp, std::shared_ptr<Revision> body);

protected:
    std::shared_ptr<ApiClient> m_ApiClient;
};

}
}
}
}

#endif /* RevisionsApi_H_ */
