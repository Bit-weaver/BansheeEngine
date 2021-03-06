//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "BsResourceManifest.h"
#include "BsResourceManifestRTTI.h"
#include "BsFileSerializer.h"
#include "BsException.h"

namespace BansheeEngine
{
	ResourceManifest::ResourceManifest(const ConstructPrivately& dummy)
	{

	}

	ResourceManifest::ResourceManifest(const String& name)
		:mName(name)
	{

	}

	SPtr<ResourceManifest> ResourceManifest::create(const String& name)
	{
		return bs_shared_ptr_new<ResourceManifest>(name);
	}

	SPtr<ResourceManifest> ResourceManifest::createEmpty()
	{
		return bs_shared_ptr_new<ResourceManifest>(ConstructPrivately());
	}

	void ResourceManifest::registerResource(const String& uuid, const Path& filePath)
	{
		auto iterFind = mUUIDToFilePath.find(uuid);

		if(iterFind != mUUIDToFilePath.end())
		{
			if (iterFind->second != filePath)
			{
				mFilePathToUUID.erase(iterFind->second);

				mUUIDToFilePath[uuid] = filePath;
				mFilePathToUUID[filePath] = uuid;
			}
		}
		else
		{
			auto iterFind2 = mFilePathToUUID.find(filePath);
			if (iterFind2 != mFilePathToUUID.end())
				mUUIDToFilePath.erase(iterFind2->second);

			mUUIDToFilePath[uuid] = filePath;
			mFilePathToUUID[filePath] = uuid;
		}
	}

	void ResourceManifest::unregisterResource(const String& uuid)
	{
		auto iterFind = mUUIDToFilePath.find(uuid);

		if(iterFind != mUUIDToFilePath.end())
		{
			mFilePathToUUID.erase(iterFind->second);
			mUUIDToFilePath.erase(uuid);
		}
	}

	bool ResourceManifest::uuidToFilePath(const String& uuid, Path& filePath) const
	{
		auto iterFind = mUUIDToFilePath.find(uuid);

		if(iterFind != mUUIDToFilePath.end())
		{
			filePath = iterFind->second;
			return true;
		}
		else
		{
			filePath = Path::BLANK;
			return false;
		}
	}

	bool ResourceManifest::filePathToUUID(const Path& filePath, String& outUUID) const
	{
		auto iterFind = mFilePathToUUID.find(filePath);

		if(iterFind != mFilePathToUUID.end())
		{
			outUUID = iterFind->second;
			return true;
		}
		else
		{
			outUUID = StringUtil::BLANK;
			return false;
		}
	}

	bool ResourceManifest::uuidExists(const String& uuid) const
	{
		auto iterFind = mUUIDToFilePath.find(uuid);

		return iterFind != mUUIDToFilePath.end();
	}

	bool ResourceManifest::filePathExists(const Path& filePath) const
	{
		auto iterFind = mFilePathToUUID.find(filePath);

		return iterFind != mFilePathToUUID.end();
	}

	void ResourceManifest::save(const SPtr<ResourceManifest>& manifest, const Path& path, const Path& relativePath)
	{
		SPtr<ResourceManifest> copy = create(manifest->mName);

		for(auto& elem : manifest->mFilePathToUUID)
		{
			if (!relativePath.includes(elem.first))
			{
				BS_EXCEPT(InvalidStateException, "Path in resource manifest cannot be made relative to: \"" + 
					relativePath.toString() + "\". Path: \"" + elem.first.toString() + "\"");
			}

			Path elementRelativePath = elem.first.getRelative(relativePath);

			copy->mFilePathToUUID[elementRelativePath] = elem.second;
		}

		for(auto& elem : manifest->mUUIDToFilePath)
		{
			if(!relativePath.includes(elem.second))
			{
				BS_EXCEPT(InvalidStateException, "Path in resource manifest cannot be made relative to: \"" + 
					relativePath.toString() + "\". Path: \"" + elem.second.toString() + "\"");
			}

			Path elementRelativePath = elem.second.getRelative(relativePath);

			copy->mUUIDToFilePath[elem.first] = elementRelativePath;
		}

		FileEncoder fs(path);
		fs.encode(copy.get());
	}

	SPtr<ResourceManifest> ResourceManifest::load(const Path& path, const Path& relativePath)
	{
		FileDecoder fs(path);
		SPtr<ResourceManifest> manifest = std::static_pointer_cast<ResourceManifest>(fs.decode());

		SPtr<ResourceManifest> copy = create(manifest->mName);

		for(auto& elem : manifest->mFilePathToUUID)
		{
			Path absPath = elem.first.getAbsolute(relativePath);
			copy->mFilePathToUUID[absPath] = elem.second;
		}

		for(auto& elem : manifest->mUUIDToFilePath)
		{
			Path absPath = elem.second.getAbsolute(relativePath);
			copy->mUUIDToFilePath[elem.first] = absPath;
		}

		return copy;
	}

	RTTITypeBase* ResourceManifest::getRTTIStatic()
	{
		return ResourceManifestRTTI::instance();
	}

	RTTITypeBase* ResourceManifest::getRTTI() const
	{
		return ResourceManifest::getRTTIStatic();
	}
}