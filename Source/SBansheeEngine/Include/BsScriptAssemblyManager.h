//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "BsManagedSerializableObjectInfo.h"
#include "BsModule.h"

namespace BansheeEngine
{
	/** @addtogroup SBansheeEngine
	 *  @{
	 */

	/**	Stores data about managed serializable objects in specified assemblies. */
	class BS_SCR_BE_EXPORT ScriptAssemblyManager : public Module<ScriptAssemblyManager>
	{
	public:
		ScriptAssemblyManager();
		~ScriptAssemblyManager();

		/**
		 * Loads all information about managed serializable objects in an assembly with the specified name. Assembly must be
		 * currently loaded. Once the data has been loaded you will be able to call getSerializableObjectInfo() and
		 * hasSerializableObjectInfo() to retrieve information about those objects. If an assembly already had data loaded
		 * it will be rebuilt.
		 */
		void loadAssemblyInfo(const String& assemblyName);

		/**	Clears any assembly data previously loaded with loadAssemblyInfo(). */
		void clearAssemblyInfo();

		/**
		 * Returns managed serializable object info for a specific managed type.
		 *
		 * @param[in]	ns			Namespace of the type.
		 * @param[in]	typeName	Name of the type.
		 * @param[out]	outInfo		Output object containing information about the type if the type was found, unmodified
		 *							otherwise.
		 * @return					True if the type was found, false otherwise.
		 */
		bool getSerializableObjectInfo(const String& ns, const String& typeName, 
			SPtr<ManagedSerializableObjectInfo>& outInfo);

		/**	Generates or retrieves a type info object for the specified managed class, if the class is serializable. */
		SPtr<ManagedSerializableTypeInfo> getTypeInfo(MonoClass* monoClass);

		/**
		 * Checks if the managed serializable object info for the specified type exists.
		 *
		 * @param[in]	ns			Namespace of the type.
		 * @param[in]	typeName	Name of the type.
		 * @return					True if the object info was found, false otherwise.
		 */
		bool hasSerializableObjectInfo(const String& ns, const String& typeName);

		/**	Returns names of all assemblies that currently have managed serializable object data loaded. */
		Vector<String> getScriptAssemblies() const;

		/**	Gets the managed class for System.Array type. */
		MonoClass* getSystemArrayClass() const { return mSystemArrayClass; }

		/**	Gets the managed class for System.Collections.Generic.List<T> type. */
		MonoClass* getSystemGenericListClass() const { return mSystemGenericListClass; }

		/**	Gets the managed class for System.Collections.Generic.Dictionary<T,U> type. */
		MonoClass* getSystemGenericDictionaryClass() const { return mSystemGenericDictionaryClass; }

		/**	Gets the managed class for System.Type type. */
		MonoClass* getSystemTypeClass() const { return mSystemTypeClass; }

		/**	Gets the managed class for BansheeEngine.Component type. */
		MonoClass* getComponentClass() const { return mComponentClass; }

		/**	Gets the managed class for BansheeEngine.MissingComponent type. */
		MonoClass* getMissingComponentClass() const { return mMissingComponentClass; }

		/**	Gets the managed class for BansheeEngine.SceneObject type. */
		MonoClass* getSceneObjectClass() const { return mSceneObjectClass; }
	private:
		/**	Deletes all stored managed serializable object infos for all assemblies. */
		void clearScriptObjects();

		/**
		 * Initializes the base managed types. These are the types we expect must exist in loaded assemblies as they're used
		 * for various common operations.
		 */
		void initializeBaseTypes();

		UnorderedMap<String, SPtr<ManagedSerializableAssemblyInfo>> mAssemblyInfos;
		bool mBaseTypesInitialized;

		MonoClass* mSystemArrayClass;
		MonoClass* mSystemGenericListClass;
		MonoClass* mSystemGenericDictionaryClass;
		MonoClass* mSystemTypeClass;

		MonoClass* mComponentClass;
		MonoClass* mSceneObjectClass;
		MonoClass* mMissingComponentClass;

		MonoClass* mSerializeObjectAttribute;
		MonoClass* mDontSerializeFieldAttribute;
		MonoClass* mSerializeFieldAttribute;
		MonoClass* mHideInInspectorAttribute;
	};

	/** @} */
}