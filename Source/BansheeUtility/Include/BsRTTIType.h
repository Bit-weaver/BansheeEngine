//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include <string>
#include <algorithm>
#include <unordered_map>

#include "BsPrerequisitesUtil.h"
#include "BsManagedDataBlock.h"
#include "BsRTTIField.h"
#include "BsRTTIPlainField.h"
#include "BsRTTIReflectableField.h"
#include "BsRTTIReflectablePtrField.h"
#include "BsRTTIManagedDataBlockField.h"
#include "BsIReflectable.h"
#include "BsBinaryDiff.h"

namespace BansheeEngine
{
	/** @addtogroup RTTI
	 *  @{
	 */

	/** Similar to BS_PLAIN_MEMBER but allows you to specify name of the field and the variable it's referencing separately. */
#define BS_PLAIN_MEMBER_NAMED(name, field)														\
	decltype(OwnerType::field)& get##name(OwnerType* obj) { return obj->field; }				\
	void set##name(OwnerType* obj, decltype(OwnerType::field)& val) { obj->field = val; } 

	/** Similar to BS_REFL_MEMBER but allows you to specify name of the field and the variable it's referencing separately. */
#define BS_REFL_MEMBER_NAMED(name, field)														\
	decltype(OwnerType::field)& get##name(OwnerType* obj) { return obj->field; }				\
	void set##name(OwnerType* obj, decltype(OwnerType::field)& val) { obj->field = val; } 

	/** Similar to BS_REFLPTR_MEMBER but allows you to specify name of the field and the variable it's referencing separately. */
#define BS_REFLPTR_MEMBER_NAMED(name, field)													\
	decltype(OwnerType::field) get##name(OwnerType* obj) { return obj->field; }					\
	void set##name(OwnerType* obj, decltype(OwnerType::field) val) { obj->field = val; } 

	/** Shortcut for defining getter/setter methods for a RTTI plain field. */
#define BS_PLAIN_MEMBER(name)																	\
	decltype(OwnerType::name)& get##name(OwnerType* obj) { return obj->name; }					\
	void set##name(OwnerType* obj, decltype(OwnerType::name)& val) { obj->name = val; } 

	/** Shortcut for defining getter/setter methods for a RTTI reflectable field. */
#define BS_REFL_MEMBER(name)																	\
	decltype(OwnerType::name)& get##name(OwnerType* obj) { return obj->name; }					\
	void set##name(OwnerType* obj, decltype(OwnerType::name)& val) { obj->name = val; } 

	/** Shortcut for defining getter/setter methods for a RTTI reflectable pointer field. */
#define BS_REFLPTR_MEMBER(name)								\
	decltype(OwnerType::name) get##name(OwnerType* obj) { return obj->name; }				\
	void set##name(OwnerType* obj, decltype(OwnerType::name) val) { obj->name = val; } 

	/** Registers a plain field defined with BS_PLAIN_MEMBER or BS_PLAIN_MEMBER_NAMED with the RTTI object. */
#define BS_ADD_PLAIN_FIELD(name, id) \
	addPlainField(#name, id, &MyType::get##name, &MyType::set##name);

	/** Registers a plain field defined with BS_REFL_MEMBER or BS_REFL_MEMBER_NAMED with the RTTI object. */
#define BS_ADD_REFL_FIELD(name, id) \
	addReflectableField(#name, id, &MyType::get##name, &MyType::set##name);

	/** Registers a plain field defined with BS_REFLPTR_MEMBER or BS_REFLPTR_MEMBER_NAMED with the RTTI object. */
#define BS_ADD_REFLPTR_FIELD(name, id) \
	addReflectablePtrField(#name, id, &MyType::get##name, &MyType::set##name);

	/** Shortcut for defining getter/setter methods for a RTTI plain Vector<T> field. */
#define BS_PLAIN_MEMBER_VEC(name)								\
	std::common_type<decltype(OwnerType::name)>::type::value_type& get##name(OwnerType* obj, UINT32 idx) { return obj->name[idx]; }				\
	void set##name(OwnerType* obj, UINT32 idx, std::common_type<decltype(OwnerType::name)>::type::value_type& val) { obj->name[idx] = val; }		\
	UINT32 getSize##name(OwnerType* obj) { return (UINT32)obj->name.size(); }	\
	void setSize##name(OwnerType* obj, UINT32 val) { obj->name.resize(val); }

	/** Shortcut for defining getter/setter methods for a RTTI reflectable Vector<T> field. */
#define BS_REFL_MEMBER_VEC(name)								\
	std::common_type<decltype(OwnerType::name)>::type::value_type& get##name(OwnerType* obj, UINT32 idx) { return obj->name[idx]; }				\
	void set##name(OwnerType* obj, UINT32 idx, std::common_type<decltype(OwnerType::name)>::type::value_type& val) { obj->name[idx] = val; }		\
	UINT32 getSize##name(OwnerType* obj) { return (UINT32)obj->name.size(); }	\
	void setSize##name(OwnerType* obj, UINT32 val) { obj->name.resize(val); }

	/** Shortcut for defining getter/setter methods for a RTTI reflectable pointer Vector<T> field. */
#define BS_REFLPTR_MEMBER_VEC(name)								\
	std::common_type<decltype(OwnerType::name)>::type::value_type get##name(OwnerType* obj, UINT32 idx) { return obj->name[idx]; }				\
	void set##name(OwnerType* obj, UINT32 idx, std::common_type<decltype(OwnerType::name)>::type::value_type val) { obj->name[idx] = val; }		\
	UINT32 getSize##name(OwnerType* obj) { return (UINT32)obj->name.size(); }	\
	void setSize##name(OwnerType* obj, UINT32 val) { obj->name.resize(val); }

	/** Registers a plain array field defined with BS_PLAIN_MEMBER_VEC with the RTTI object. */
#define BS_ADD_PLAIN_FIELD_ARR(name, id) \
	addPlainArrayField(#name, id, &MyType::get##name, &MyType::getSize##name, \
	&MyType::set##name, &MyType::setSize##name);

	/** Registers a reflectable object array field defined with BS_PLAIN_MEMBER_VEC with the RTTI object. */
#define BS_ADD_REFL_FIELD_ARR(name, id) \
	addReflectableArrayField(#name, id, &MyType::get##name, &MyType::getSize##name, \
	&MyType::set##name, &MyType::setSize##name);

	/** Registers a reflectable pointer array field defined with BS_PLAIN_MEMBER_VEC with the RTTI object. */
#define BS_ADD_REFLPTR_FIELD_ARR(name, id) \
	addReflectablePtrArrayField(#name, id, &MyType::get##name, &MyType::getSize##name, \
	&MyType::set##name, &MyType::setSize##name);

	/** @} */

	/** @addtogroup Internal-Utility
	 *  @{
	 */
	/** @addtogroup RTTI-Internal
	 *  @{
	 */

	/**
	 * Provides an interface for accessing fields of a certain class.
	 * Data can be easily accessed by getter and setter methods.
	 * 			
	 * Supported data types:
	 *	- Plain types - All types defined in BsRTTIField.h, mostly native types and POD (plain old data) structs. Data is parsed byte by byte.  
	 *	                No pointers to plain types are supported. Data is passed around by value.
	 *	- Reflectable types - Any class deriving from IReflectable. Data is parsed based on fields in its RTTI class. Can be pointer or value type.
	 *	- Arrays of both plain and reflectable types are supported
	 *	- Data blocks - A managed or unmanaged block of data. See ManagedDataBlock.
	 */
	class BS_UTILITY_EXPORT RTTITypeBase
	{
	public:
		RTTITypeBase();
		virtual ~RTTITypeBase();

		/** Returns RTTI type information for all classes that derive from the class that owns this RTTI type. */
		virtual Vector<RTTITypeBase*>& getDerivedClasses() = 0;

		/**
		 * Returns RTTI type information for the class that owns this RTTI type. If the class has not base type, null is 
		 * returned instead.
		 */
		virtual RTTITypeBase* getBaseClass() = 0;

		/** Returns true if current RTTI class is derived from @p base. (Or if it is the same type as base) */
		virtual bool isDerivedFrom(RTTITypeBase* base) = 0;

		/** Creates a new instance of the class owning this RTTI type. */
		virtual SPtr<IReflectable> newRTTIObject() = 0;

		/** Returns the name of the class owning this RTTI type. */
		virtual const String& getRTTIName() = 0;

		/** Returns an RTTI id that uniquely represents each class in the RTTI system. */
		virtual UINT32 getRTTIId() = 0;

		/**
		 * Called by the serializers when serialization for this object has started. Use this to do any preprocessing on 
		 * data you might need during serialization itself.
		 */
		virtual void onSerializationStarted(IReflectable* obj) {}

		/**
		 * Called by the serializers when serialization for this object has ended. After serialization has ended you can 
		 * be sure that the type has been fully serialized, and you may clean up any temporary data.
		 */
		virtual void onSerializationEnded(IReflectable* obj) {}

		/**
		 * Called by the serializers when deserialization for this object has started. Use this to do any preprocessing 
		 * on data you might need during deserialization itself.
		 */
		virtual void onDeserializationStarted(IReflectable* obj) {}

		/**
		 * Called by the serializers when deserialization for this object has ended. At this point you can be sure the 
		 * instance has been fully deserialized and you may safely use it.
		 *
		 * One exception being are fields you marked with RTTI_Flag_WeakRef, as they might be resolved only after 
		 * deserialization has fully completed for all objects.
		 */
		virtual void onDeserializationEnded(IReflectable* obj) {}

		/**
		 * Returns a handler that determines how are "diffs" generated and applied when it comes to objects of this RTTI 
		 * type. A "diff" is a list of differences between two objects that may be saved, viewed or applied to another 
		 * object to transform it.
		 */
		virtual IDiff& getDiffHandler() const
		{
			static BinaryDiff diffHandler;
			return diffHandler;
		}

		/**
		 * Allows you to assign a value to a plain field with the specified name on the provided instance.
		 *
		 * @note	Caller must ensure instance and value types are valid for this field.
		 */
		template <class ObjectType, class DataType>
		void setPlainValue(ObjectType* object, const String& name, DataType& value)
		{
			RTTIField* genericField = findField(name);
			genericField->checkIsPlain(false);

			RTTIPlainFieldBase* field = static_cast<RTTIPlainFieldBase*>(genericField);

			UINT32 typeSize = 0;
			if(RTTIPlainType<DataType>::hasDynamicSize)
				typeSize = RTTIPlainType<DataType>::getDynamicSize(value);
			else
				typeSize = sizeof(DataType);

			UINT8* tempBuffer = (UINT8*)bs_stack_alloc(typeSize);
			RTTIPlainType<DataType>::toMemory(value, (char*)tempBuffer);
			
			field->fromBuffer(object, tempBuffer);

			bs_stack_free(tempBuffer);
		}

		/**
		 * Allows you to assign a value to a plain field array element with the specified name and index on the provided instance.
		 *
		 * @note	Caller must ensure instance and value types are valid for this field.
		 */
		template <class ObjectType, class DataType>
		void setPlainArrayValue(ObjectType* object, const String& name, UINT32 index, DataType& value)
		{
			RTTIField* genericField = findField(name);
			genericField->checkIsPlain(true);

			RTTIPlainFieldBase* field = static_cast<RTTIPlainFieldBase*>(genericField);

			UINT32 typeSize = 0;
			if(RTTIPlainType<DataType>::hasDynamicSize)
				typeSize = RTTIPlainType<DataType>::getDynamicSize(value);
			else
				typeSize = sizeof(DataType);

			UINT8* tempBuffer = (UINT8*)bs_stack_alloc(typeSize);
			RTTIPlainType<DataType>::toMemory(value, (char*)tempBuffer);

			field->arrayElemFromBuffer(object, index, tempBuffer);

			bs_stack_free(tempBuffer);
		}

		/**
		 * Allows you to assign a value to a reflectable field with the specified name on the provided instance.
		 *
		 * @note	Caller must ensure instance and value types are valid for this field.
		 */
		template <class ObjectType, class DataType>
		void setReflectableValue(ObjectType* object, const String& name, DataType& value)
		{
			static_assert((std::is_base_of<BansheeEngine::IReflectable, DataType>::value), 
				"Invalid data type for complex field. It needs to derive from BansheeEngine::IReflectable.");

			RTTIField* genericField = findField(name);
			genericField->checkIsComplex(false);

			RTTIReflectableFieldBase* field = static_cast<RTTIReflectableFieldBase*>(genericField);
			field->setValue(object, value);
		}

		/**
		 * Allows you to assign a value to a reflectable field array element with the specified name and index on the 
		 * provided instance.
		 *
		 * @note	Caller must ensure instance and value types are valid for this field.
		 */
		template <class ObjectType, class DataType>
		void setReflectableArrayValue(ObjectType* object, const String& name, UINT32 index, DataType& value)
		{
			static_assert((std::is_base_of<BansheeEngine::IReflectable, DataType>::value), 
				"Invalid data type for complex field. It needs to derive from BansheeEngine::IReflectable.");

			RTTIField* genericField = findField(name);
			genericField->checkIsComplex(true);

			RTTIReflectableFieldBase* field = static_cast<RTTIReflectableFieldBase*>(genericField);
			field->setArrayValue(object, index, value);
		}

		/**
		 * Allows you to assign a value to a managed data block field with the specified name on the provided instance.
		 *
		 * @note	Caller must ensure instance type is valid for this field.
		 */
		template <class ObjectType>
		void setDataBlockValue(ObjectType* object, const String& name, ManagedDataBlock value)
		{
			RTTIField* genericField = findField(name);
			genericField->checkIsDataBlock();

			RTTIManagedDataBlockFieldBase* field = static_cast<RTTIManagedDataBlockFieldBase*>(genericField);
			field->setValue(object, value);
		}

		/**
		 * Allows you to assign a value to a reflectable pointer field with the specified name on the provided instance.
		 *
		 * @note	Caller must ensure instance and value types are valid for this field.
		 */
		template <class ObjectType, class DataType>
		void setReflectablePtrValue(ObjectType* object, const String& name, SPtr<DataType> value)
		{
			static_assert((std::is_base_of<BansheeEngine::IReflectable, DataType>::value), 
				"Invalid data type for complex field. It needs to derive from BansheeEngine::IReflectable.");

			RTTIField* genericField = findField(name);
			genericField->checkIsComplexPtr(false);

			RTTIReflectablePtrFieldBase* field = static_cast<RTTIReflectablePtrFieldBase*>(genericField);
			field->setValue(object, value);
		}

		/**
		 * Allows you to assign a value to a reflectable pointer field array element with the specified name and index on 
		 * the provided instance.
		 *
		 * @note	Caller must ensure instance and value types are valid for this field.
		 */
		template <class ObjectType, class DataType>
		void setReflectablePtrArrayValue(ObjectType* object, const String& name, UINT32 index, SPtr<DataType> value)
		{
			static_assert((std::is_base_of<BansheeEngine::IReflectable, DataType>::value), 
				"Invalid data type for complex field. It needs to derive from BansheeEngine::IReflectable.");

			RTTIField* genericField = findField(name);
			genericField->checkIsComplexPtr(true);

			RTTIReflectablePtrFieldBase* field = static_cast<RTTIReflectablePtrFieldBase*>(genericField);
			field->setArrayValue(object, index, value);
		}

		/**
		 * Reads a value from a plain field with the specified name from the provided instance.
		 *
		 * @note	Caller must ensure instance and value types are valid for this field.
		 */
		template <class ObjectType, class DataType>
		void getPlainValue(ObjectType* object, const String& name, DataType& value)
		{
			RTTIField* genericField = findField(name);
			genericField->checkIsPlain(false);

			RTTIPlainFieldBase* field = static_cast<RTTIPlainFieldBase*>(genericField);

			UINT32 typeSize = 0;
			if(field->hasDynamicSize())
				typeSize = field->getDynamicSize(object);
			else
				typeSize = field->getTypeSize();

			UINT8* tempBuffer = (UINT8*)bs_stack_alloc(typeSize);

			field->toBuffer(object, tempBuffer);
			RTTIPlainType<DataType>::fromMemory(value, (char*)tempBuffer);

			bs_stack_free(tempBuffer);
		}

		/**
		 * Reads a value from a plain array field with the specified name and index from the provided instance.
		 *
		 * @note	Caller must ensure instance and value types are valid for this field.
		 */
		template <class ObjectType, class DataType>
		void getPlainArrayValue(ObjectType* object, const String& name, UINT32 index, DataType& value)
		{
			RTTIField* genericField = findField(name);
			genericField->checkIsPlain(true);

			RTTIPlainFieldBase* field = static_cast<RTTIPlainFieldBase*>(genericField);

			UINT32 typeSize = 0;
			if(field->hasDynamicSize())
				typeSize = field->getArrayElemDynamicSize(object, arrIdx);
			else
				typeSize = field->getTypeSize();

			UINT8* tempBuffer = (UINT8*)bs_stack_alloc(typeSize);

			field->arrayElemToBuffer(object, index, tempBuffer);
			RTTIPlainType<DataType>::fromMemory(value, (char*)tempBuffer);

			bs_stack_free(tempBuffer);
		}	

		/**
		 * Reads a value from a reflectable object field with the specified name from the provided instance.
		 *
		 * @note	Caller must ensure instance and value types are valid for this field.
		 */
		template <class ObjectType>
		IReflectable& getReflectableValue(ObjectType* object, const String& name)
		{
			RTTIField* genericField = findField(name);
			genericField->checkIsComplex(false);

			RTTIReflectableFieldBase* field = static_cast<RTTIReflectableFieldBase*>(genericField);
			return field->getValue(object);
		}

		/**
		 * Reads a value from a reflectable object array field with the specified name and index from the provided instance.
		 *
		 * @note	Caller must ensure instance and value types are valid for this field.
		 */
		template <class ObjectType>
		IReflectable& getReflectableArrayValue(ObjectType* object, const String& name, UINT32 index)
		{
			RTTIField* genericField = findField(name);
			genericField->checkIsComplex(true);

			RTTIReflectableFieldBase* field = static_cast<RTTIReflectableFieldBase*>(genericField);
			return field->getArrayValue(object, index);
		}

		/**
		 * Reads a managed data block field with the specified name from the provided instance.
		 *
		 * @note	Caller must ensure instance type is valid for this field.
		 */
		template <class ObjectType>
		ManagedDataBlock getDataBlockValue(ObjectType* object, const String& name)
		{
			RTTIField* genericField = findField(name);
			genericField->checkIsDataBlock();

			RTTIManagedDataBlockFieldBase* field = static_cast<RTTIManagedDataBlockFieldBase*>(genericField);
			return field->getValue(object);
		}

		/**
		 * Reads a value from a reflectable object pointer field with the specified name from the provided instance.
		 *
		 * @note	Caller must ensure instance and value types are valid for this field.
		 */
		template <class ObjectType>
		SPtr<IReflectable> getReflectablePtrValue(ObjectType* object, const String& name)
		{
			RTTIField* genericField = findField(name);
			genericField->checkIsComplexPtr(false);

			RTTIReflectablePtrFieldBase* field = static_cast<RTTIReflectablePtrFieldBase*>(genericField);
			return field->getValue(object);
		}

		/**
		 * Reads a value from a reflectable pointer array field with the specified name and index from the provided instance.
		 *
		 * @note	Caller must ensure instance and value types are valid for this field.
		 */
		template <class ObjectType>
		SPtr<IReflectable> getReflectablePtrArrayValue(ObjectType* object, const String& name, UINT32 index)
		{
			RTTIField* genericField = findField(name);
			genericField->checkIsComplexPtr(true);

			RTTIReflectablePtrFieldBase* field = static_cast<RTTIReflectablePtrFieldBase*>(genericField);
			return field->getArrayValue(object, index);
		}

		/**
		 * Returns the size of the array of the field with the specified name on the provided instance.
		 *
		 * @note	Caller must ensure instance type is valid and that the field as an array.
		 */
		template <class ObjectType>
		UINT32 getArraySize(ObjectType* object, const String& name)
		{
			RTTIField* field = findField(name);
			return field->getArraySize(object);
		}

		/**
		 * Sets the size of the array of the field with the specified name on the provided instance.
		 *
		 * @note	
		 * Caller must ensure instance type is valid and that the field as an array. This might clear any existing data 
		 * from the array.
		 */
		template <class ObjectType>
		void setArraySize(ObjectType* object, const String& name, UINT32 size)
		{
			RTTIField* field = findField(name);
			field->setArraySize(object, size);
		}	

		/** Returns the total number of fields in this RTTI type. */
		UINT32 getNumFields() const { return (UINT32)mFields.size(); }

		/** Returns a field based on the field index. Use getNumFields() to get total number of fields available. */
		RTTIField* getField(UINT32 idx) { return mFields.at(idx); }

		/**
		 * Tries to find a field with the specified name. Throws an exception if it can't.
		 *
		 * @param	name	The name of the field.
		 */
		RTTIField* findField(const String& name);

		/**
		 * Tries to find a field with the specified unique ID. Doesn't throw an exception if it can't find the field 
		 * (Unlike findField(const String&)). 
		 *
		 * @param	uniqueFieldId	Unique identifier for the field.
		 *
		 * @return	nullptr if it can't find the field.
		 */
		RTTIField* findField(int uniqueFieldId);

		/** @name Internal 
		 *  @{
		 */

		/** Called by the RTTI system when a class is first found in order to form child/parent class hierarchy. */
		virtual void _registerDerivedClass(RTTITypeBase* derivedClass) = 0;

		/** @} */

	protected:
		/**
		 * Tries to add a new field to the fields array, and throws an exception if a field with the same name or id 
		 * already exists.
		 *
		 * @param[in]	field	Field, must be non-null.
		 */
		void addNewField(RTTIField* field);

	private:
		Vector<RTTIField*> mFields;
	};

	/** Used for initializing a certain type as soon as the program is loaded. */
	template<typename Type, typename BaseType>
	struct InitRTTIOnStart
	{
	public:
		InitRTTIOnStart()
		{
			BaseType::getRTTIStatic()->_registerDerivedClass(Type::getRTTIStatic());
		}

		void makeSureIAmInstantiated() { }
	};

	/** Specialization for root class of RTTI hierarchy - IReflectable */
	template<typename Type>
	struct InitRTTIOnStart<Type, IReflectable>
	{
	public:
		InitRTTIOnStart()
		{
			IReflectable::_registerDerivedClass(Type::getRTTIStatic());
		}

		void makeSureIAmInstantiated() { }
	};

	/**
	 * Template that returns RTTI type of the specified type, unless the specified type is IReflectable in which case it 
	 * returns a null.
	 */
	template<typename Type>
	struct GetRTTIType
	{
		RTTITypeBase* operator()() { return Type::getRTTIStatic(); }
	};

	/** Specialization for root class of RTTI hierarchy - IReflectable. */
	template<>
	struct GetRTTIType<IReflectable>
	{
		RTTITypeBase* operator()() { return nullptr; }
	};

	/** @} */
	/** @} */

	/** @addtogroup RTTI
	 *  @{
	 */

	/**
	 * Allows you to provide a run-time type information for a specific class, along with support for 
	 * serialization/deserialization.
	 * 			
	 * Derive from this class and return the that class from IReflectable::getRTTI. This way you can separate serialization 
	 * logic from the actual class you're serializing.
	 *
	 * This class will provide a way to register individual fields in the class, together with ways to read and write them, 
	 * as well a providing information about class hierarchy, and run-time type checking.
	 */
	template <typename Type, typename BaseType, typename MyRTTIType>
	class RTTIType : public RTTITypeBase
	{
	protected:
		/************************************************************************/
		/* 						RTTI CLASS META DATA							*/
		/************************************************************************/

		static InitRTTIOnStart<Type, BaseType> initOnStart;

	public:
		RTTIType() 
		{
			// Compiler will only generate code for stuff that is directly used, including static data members,
			// so we fool it here like we're using the class directly. Otherwise compiler won't generate the code for the member
			// and our type won't get initialized on start (Actual behavior is a bit more random)
			initOnStart.makeSureIAmInstantiated();
		}
		virtual ~RTTIType() {}

		/** Returns a singleton of this RTTI type. */
		static MyRTTIType* instance()
		{
			static MyRTTIType inst;
			return &inst;
		}

		/** @copydoc RTTITypeBase::getDerivedClasses */
		Vector<RTTITypeBase*>& getDerivedClasses() override
		{
			static Vector<RTTITypeBase*> mRTTIDerivedClasses;
			return mRTTIDerivedClasses;
		}

		/** @copydoc RTTITypeBase::getBaseClass */
		RTTITypeBase* getBaseClass() override
		{
			return GetRTTIType<BaseType>()();
		}

		/** @copydoc RTTITypeBase::isDerivedFrom */
		bool isDerivedFrom(RTTITypeBase* base) override
		{
			assert(base != nullptr);

			Stack<RTTITypeBase*> todo;
			todo.push(base);

			while (!todo.empty())
			{
				RTTITypeBase* currentType = todo.top();
				todo.pop();

				if (currentType->getRTTIId() == getRTTIId())
					return true;

				const Vector<RTTITypeBase*>& derivedClasses = currentType->getDerivedClasses();
				for (auto iter = derivedClasses.begin(); iter != derivedClasses.end(); ++iter)
					todo.push(*iter);
			}

			return false;
		}

		/** @copydoc RTTITypeBase::_registerDerivedClass */
		void _registerDerivedClass(RTTITypeBase* derivedClass) override
		{
			if(IReflectable::_isTypeIdDuplicate(derivedClass->getRTTIId()))
			{
				BS_EXCEPT(InternalErrorException, "RTTI type \"" + derivedClass->getRTTIName() + 
					"\" has a duplicate ID: " + toString(derivedClass->getRTTIId()));
			}

			getDerivedClasses().push_back(derivedClass);
		}

		/************************************************************************/
		/* 			FIELDS OPERATING DIRECTLY ON SERIALIZABLE OBJECT            */
		/************************************************************************/

		/**
		 * Registers a new plain field. This field can then be accessed dynamically from the RTTI system and used for 
		 * automatic serialization. See RTTIField for more information about field types.
		 *
		 * @param[in]	name		Name of the field.
		 * @param[in]	uniqueId	Unique identifier for this field. Although name is also a unique identifier we want a 
		 *							small data type that can be used for efficiently serializing data to disk and similar. 
		 *							It is primarily used for compatibility between different versions of serialized data.
		 * @param[in]	getter  	Method used for retrieving the value of this field.
		 * @param[in]	setter  	Method used for setting the value of this field.
		 * @param[in]	flags		Various flags you can use to specialize how systems handle this field. See RTTIFieldFlag.
		 */
		template<class ObjectType, class DataType>
		void addPlainField(const String& name, UINT32 uniqueId, DataType& (ObjectType::*getter)(), 
			void (ObjectType::*setter)(DataType&) = nullptr, UINT64 flags = 0)
		{
			addPlainField<ObjectType, DataType>(name, uniqueId, 
				std::function<DataType&(ObjectType*)>(getter), 
				std::function<void(ObjectType*, DataType&)>(setter), flags);
		}

		/**
		 * Registers a new reflectable object field. This field can then be accessed dynamically from the RTTI system and
		 * used for automatic serialization. See RTTIField for more information about field types.
		 *
		 * @param[in]	name		Name of the field.
		 * @param[in]	uniqueId	Unique identifier for this field. Although name is also a unique identifier we want a 
		 *							small data type that can be used for efficiently serializing data to disk and similar. 
		 *							It is primarily used for compatibility between different versions of serialized data.
		 * @param[in]	getter  	Method used for retrieving the value of this field.
		 * @param[in]	setter  	Method used for setting the value of this field.
		 * @param[in]	flags		Various flags you can use to specialize how systems handle this field. See RTTIFieldFlag.
		 */
		template<class ObjectType, class DataType>
		void addReflectableField(const String& name, UINT32 uniqueId, DataType& (ObjectType::*getter)(), 
			void (ObjectType::*setter)(DataType&) = nullptr, UINT64 flags = 0)
		{
			addReflectableField<ObjectType, DataType>(name, uniqueId, 
				std::function<DataType&(ObjectType*)>(getter), 
				std::function<void(ObjectType*, DataType&)>(setter), flags);
		}

		/**
		 * Registers a new reflectable object pointer field. This field can then be accessed dynamically from the RTTI 
		 * system and used for automatic serialization. See RTTIField for more information about field types.
		 *
		 * @param[in]	name		Name of the field.
		 * @param[in]	uniqueId	Unique identifier for this field. Although name is also a unique identifier we want a 
		 *							small data type that can be used for efficiently serializing data to disk and similar. 
		 *							It is primarily used for compatibility between different versions of serialized data.
		 * @param[in]	getter  	Method used for retrieving the value of this field.
		 * @param[in]	setter  	Method used for setting the value of this field.
		 * @param[in]	flags		Various flags you can use to specialize how systems handle this field. See RTTIFieldFlag.
		 */
		template<class ObjectType, class DataType>
		void addReflectablePtrField(const String& name, UINT32 uniqueId, SPtr<DataType> (ObjectType::*getter)(), 
			void (ObjectType::*setter)(SPtr<DataType>) = nullptr, UINT64 flags = 0)
		{
			addReflectablePtrField<ObjectType, DataType>(name, uniqueId, 
				std::function<SPtr<DataType>(ObjectType*)>(getter), 
				std::function<void(ObjectType*, SPtr<DataType>)>(setter), flags);
		}

		/**
		 * Registers a new field containg an array of plain values. This field can then be accessed dynamically from the 
		 * RTTI system and used for automatic serialization. See RTTIField for more information about field types.
		 *
		 * @param[in]	name		Name of the field.
		 * @param[in]	uniqueId	Unique identifier for this field. Although name is also a unique identifier we want a 
		 *							small data type that can be used for efficiently serializing data to disk and similar. 
		 *							It is primarily used for compatibility between different versions of serialized data.
		 * @param[in]	getter  	Method used for retrieving a single element of the array.
		 * @param[in]	getSize 	Getter method that returns the size of the array.
		 * @param[in]	setter  	Method used for setting the a single element of the field.
		 * @param[in]	setSize 	Setter method that allows you to resize the array. 
		 * @param[in]	flags		Various flags you can use to specialize how systems handle this field. See RTTIFieldFlag.
		 */
		template<class ObjectType, class DataType>
		void addPlainArrayField(const String& name, UINT32 uniqueId, DataType& (ObjectType::*getter)(UINT32), UINT32 (ObjectType::*getSize)(), 
			void (ObjectType::*setter)(UINT32, DataType&) = nullptr, void(ObjectType::*setSize)(UINT32) = nullptr, UINT64 flags = 0)
		{
			addPlainArrayField<ObjectType, DataType>(name, uniqueId, 
				std::function<DataType&(ObjectType*, UINT32)>(getter), 
				std::function<UINT32(ObjectType*)>(getSize), 
				std::function<void(ObjectType*, UINT32, DataType&)>(setter), 
				std::function<void(ObjectType*, UINT32)>(setSize), flags);
		}	

		/**
		 * Registers a new field containg an array of reflectable object values. This field can then be accessed dynamically
		 * from the RTTI system and used for automatic serialization. See RTTIField for more information about field types.
		 *
		 * @param[in]	name		Name of the field.
		 * @param[in]	uniqueId	Unique identifier for this field. Although name is also a unique identifier we want a 
		 *							small data type that can be used for efficiently serializing data to disk and similar. 
		 *							It is primarily used for compatibility between different versions of serialized data.
		 * @param[in]	getter  	Method used for retrieving a single element of the array.
		 * @param[in]	getSize 	Getter method that returns the size of the array.
		 * @param[in]	setter  	Method used for setting the a single element of the field.
		 * @param[in]	setSize 	Setter method that allows you to resize the array. 
		 * @param[in]	flags		Various flags you can use to specialize how systems handle this field. See RTTIFieldFlag.
		 */
		template<class ObjectType, class DataType>
		void addReflectableArrayField(const String& name, UINT32 uniqueId, DataType& (ObjectType::*getter)(UINT32), UINT32 (ObjectType::*getSize)(), 
			void (ObjectType::*setter)(UINT32, DataType&) = nullptr, void(ObjectType::*setSize)(UINT32) = nullptr, UINT64 flags = 0)
		{
			addReflectableArrayField<ObjectType, DataType>(name, uniqueId, 
				std::function<DataType&(ObjectType*, UINT32)>(getter), 
				std::function<UINT32(ObjectType*)>(getSize), 
				std::function<void(ObjectType*, UINT32, DataType&)>(setter), 
				std::function<void(ObjectType*, UINT32)>(setSize), flags);
		}

		/**
		 * Registers a new field containg an array of reflectable obejct pointers. This field can then be accessed 
		 * dynamically from the RTTI system and used for automatic serialization. See RTTIField for more information 
		 * about field types.
		 *
		 * @param[in]	name		Name of the field.
		 * @param[in]	uniqueId	Unique identifier for this field. Although name is also a unique identifier we want a 
		 *							small data type that can be used for efficiently serializing data to disk and similar. 
		 *							It is primarily used for compatibility between different versions of serialized data.
		 * @param[in]	getter  	Method used for retrieving a single element of the array.
		 * @param[in]	getSize 	Getter method that returns the size of the array.
		 * @param[in]	setter  	Method used for setting the a single element of the field.
		 * @param[in]	setSize 	Setter method that allows you to resize the array. 
		 * @param[in]	flags		Various flags you can use to specialize how systems handle this field. See RTTIFieldFlag.
		 */
		template<class ObjectType, class DataType>
		void addReflectablePtrArrayField(const String& name, UINT32 uniqueId, SPtr<DataType> (ObjectType::*getter)(UINT32), UINT32 (ObjectType::*getSize)(), 
			void (ObjectType::*setter)(UINT32, SPtr<DataType>) = nullptr, void(ObjectType::*setSize)(UINT32) = nullptr, UINT64 flags = 0)
		{
			addReflectablePtrArrayField<ObjectType, DataType>(name, uniqueId, 
				std::function<SPtr<DataType>(ObjectType*, UINT32)>(getter), 
				std::function<UINT32(ObjectType*)>(getSize), 
				std::function<void(ObjectType*, UINT32, SPtr<DataType>)>(setter), 
				std::function<void(ObjectType*, UINT32)>(setSize), flags);
		}

		/**
		 * Registers a new managed data block field. This field can then be accessed dynamically from the RTTI system and
		 * used for automatic serialization. See RTTIField for more information about field types.
		 *
		 * @param[in]	name		Name of the field.
		 * @param[in]	uniqueId	Unique identifier for this field. Although name is also a unique identifier we want a 
		 *							small data type that can be used for efficiently serializing data to disk and similar. 
		 *							It is primarily used for compatibility between different versions of serialized data.
		 * @param[in]	getter  	Method used for retrieving the value of this field.
		 * @param[in]	setter  	Method used for setting the value of this field.
		 * @param[in]	flags		Various flags you can use to specialize how systems handle this field. See RTTIFieldFlag.
		 */
		template<class ObjectType>
		void addDataBlockField(const String& name, UINT32 uniqueId, ManagedDataBlock (ObjectType::*getter)(), 
			void (ObjectType::*setter)(ManagedDataBlock) = nullptr, UINT64 flags = 0, UINT8* (customAllocator)(ObjectType*, UINT32) = 0)
		{
			addDataBlockField<ObjectType>(name, uniqueId, 
				std::function<ManagedDataBlock(ObjectType*)>(getter),  
				std::function<void(ObjectType*, ManagedDataBlock)>(setter), flags, customAllocator);
		}	

	protected:
		typedef Type OwnerType;
		typedef MyRTTIType MyType;

		virtual void initSerializableFields() {}

		/************************************************************************/
		/* 		FIELDS OPERATING ON DERIVED SERIALIZATION INTERFACE				*/
		/*		(Needs an extra pointer to the actual object)					*/
		/************************************************************************/
		template<class InterfaceType, class ObjectType, class DataType>
		void addPlainField(const String& name, UINT32 uniqueId, 
			DataType& (InterfaceType::*getter)(ObjectType*), 
			void (InterfaceType::*setter)(ObjectType*, DataType&), UINT64 flags = 0)
		{
			using namespace std::placeholders;

			static_assert((std::is_base_of<BansheeEngine::RTTIType<Type, BaseType, MyRTTIType>, InterfaceType>::value), 
				"Class with the get/set methods must derive from BansheeEngine::RTTIType.");

			static_assert(!(std::is_base_of<BansheeEngine::IReflectable, DataType>::value), 
				"Data type derives from IReflectable but it is being added as a plain field.");

			addPlainField<ObjectType, DataType>(name, uniqueId, 
				std::function<DataType&(ObjectType*)>(std::bind(getter, static_cast<InterfaceType*>(this), _1)), 
				std::function<void(ObjectType*, DataType&)>(std::bind(setter, static_cast<InterfaceType*>(this), _1, _2)), flags);
		}

		template<class InterfaceType, class ObjectType, class DataType>
		void addReflectableField(const String& name, UINT32 uniqueId, 
			DataType& (InterfaceType::*getter)(ObjectType*), 
			void (InterfaceType::*setter)(ObjectType*, DataType&), UINT64 flags = 0)
		{
			using namespace std::placeholders;

			addReflectableField<ObjectType, DataType>(name, uniqueId, 
				std::function<DataType&(ObjectType*)>(std::bind(getter, static_cast<InterfaceType*>(this), _1)), 
				std::function<void(ObjectType*, DataType&)>(std::bind(setter, static_cast<InterfaceType*>(this), _1, _2)), flags);
		}

		template<class InterfaceType, class ObjectType, class DataType>
		void addReflectablePtrField(const String& name, UINT32 uniqueId, 
			SPtr<DataType> (InterfaceType::*getter)(ObjectType*), 
			void (InterfaceType::*setter)(ObjectType*, SPtr<DataType>), UINT64 flags = 0)
		{
			using namespace std::placeholders;

			addReflectablePtrField<ObjectType, DataType>(name, uniqueId, 
				std::function<SPtr<DataType>(ObjectType*)>(std::bind(getter, static_cast<InterfaceType*>(this), _1)), 
				std::function<void(ObjectType*, SPtr<DataType>)>(std::bind(setter, static_cast<InterfaceType*>(this), _1, _2)), flags);
		}

		template<class InterfaceType, class ObjectType, class DataType>
		void addPlainArrayField(const String& name, UINT32 uniqueId, 
			DataType& (InterfaceType::*getter)(ObjectType*, UINT32), 
			UINT32 (InterfaceType::*getSize)(ObjectType*), 
			void (InterfaceType::*setter)(ObjectType*, UINT32, DataType&), 
			void(InterfaceType::*setSize)(ObjectType*, UINT32), UINT64 flags = 0)
		{
			using namespace std::placeholders;

			static_assert((std::is_base_of<BansheeEngine::RTTIType<Type, BaseType, MyRTTIType>, InterfaceType>::value), 
				"Class with the get/set methods must derive from BansheeEngine::RTTIType.");

			static_assert(!(std::is_base_of<BansheeEngine::IReflectable, DataType>::value), 
				"Data type derives from IReflectable but it is being added as a plain field.");

			addPlainArrayField<ObjectType, DataType>(name, uniqueId, 
				std::function<DataType&(ObjectType*, UINT32)>(std::bind(getter, static_cast<InterfaceType*>(this), _1, _2)), 
				std::function<UINT32(ObjectType*)>(std::bind(getSize, static_cast<InterfaceType*>(this), _1)), 
				std::function<void(ObjectType*, UINT32, DataType&)>(std::bind(setter, static_cast<InterfaceType*>(this), _1, _2, _3)), 
				std::function<void(ObjectType*, UINT32)>(std::bind(setSize, static_cast<InterfaceType*>(this), _1, _2)), flags);
		}	

		template<class InterfaceType, class ObjectType, class DataType>
		void addReflectableArrayField(const String& name, UINT32 uniqueId, 
			DataType& (InterfaceType::*getter)(ObjectType*, UINT32), 
			UINT32 (InterfaceType::*getSize)(ObjectType*), 
			void (InterfaceType::*setter)(ObjectType*, UINT32, DataType&), 
			void(InterfaceType::*setSize)(ObjectType*, UINT32), UINT64 flags = 0)
		{
			using namespace std::placeholders;

			addReflectableArrayField<ObjectType, DataType>(name, uniqueId, 
				std::function<DataType&(ObjectType*, UINT32)>(std::bind(getter, static_cast<InterfaceType*>(this), _1, _2)), 
				std::function<UINT32(ObjectType*)>(std::bind(getSize, static_cast<InterfaceType*>(this), _1)), 
				std::function<void(ObjectType*, UINT32, DataType&)>(std::bind(setter, static_cast<InterfaceType*>(this), _1, _2, _3)), 
				std::function<void(ObjectType*, UINT32)>(std::bind(setSize, static_cast<InterfaceType*>(this), _1, _2)), flags);
		}

		template<class InterfaceType, class ObjectType, class DataType>
		void addReflectablePtrArrayField(const String& name, UINT32 uniqueId, 
			SPtr<DataType> (InterfaceType::*getter)(ObjectType*, UINT32), 
			UINT32 (InterfaceType::*getSize)(ObjectType*), 
			void (InterfaceType::*setter)(ObjectType*, UINT32, SPtr<DataType>), 
			void(InterfaceType::*setSize)(ObjectType*, UINT32), UINT64 flags = 0)
		{
			using namespace std::placeholders;

			addReflectablePtrArrayField<ObjectType, DataType>(name, uniqueId, 
				std::function<SPtr<DataType>(ObjectType*, UINT32)>(std::bind(getter, static_cast<InterfaceType*>(this), _1, _2)), 
				std::function<UINT32(ObjectType*)>(std::bind(getSize, static_cast<InterfaceType*>(this), _1)), 
				std::function<void(ObjectType*, UINT32, SPtr<DataType>)>(std::bind(setter, static_cast<InterfaceType*>(this), _1, _2, _3)), 
				std::function<void(ObjectType*, UINT32)>(std::bind(setSize, static_cast<InterfaceType*>(this), _1, _2)), flags);
		}

		template<class InterfaceType, class ObjectType>
		void addDataBlockField(const String& name, UINT32 uniqueId, ManagedDataBlock (InterfaceType::*getter)(ObjectType*), 
			void (InterfaceType::*setter)(ObjectType*, ManagedDataBlock), UINT64 flags = 0, 
			UINT8* (customAllocator)(ObjectType*, UINT32) = 0)
		{
			using namespace std::placeholders;

			if(customAllocator != 0)
			{
				std::function<UINT8*(ObjectType*, UINT32)> customAllocFunc = std::bind(customAllocator, _1, _2);

				addDataBlockField<ObjectType>(name, uniqueId, 
					std::function<ManagedDataBlock(ObjectType*)>(std::bind(getter, static_cast<InterfaceType*>(this), _1)),  
					std::function<void(ObjectType*, ManagedDataBlock)>(std::bind(setter, static_cast<InterfaceType*>(this), _1, _2)), flags, 
					customAllocFunc);
			}
			else
			{
				addDataBlockField<ObjectType>(name, uniqueId, 
					std::function<ManagedDataBlock(ObjectType*)>(std::bind(getter, static_cast<InterfaceType*>(this), _1)),  
					std::function<void(ObjectType*, ManagedDataBlock)>(std::bind(setter, static_cast<InterfaceType*>(this), _1, _2)), flags);
			}
		}	

	private:
		template<class ObjectType, class DataType>
		void addPlainField(const String& name, UINT32 uniqueId, Any getter, Any setter, UINT64 flags)
		{
			RTTIPlainField<DataType, ObjectType>* newField = 
				bs_new<RTTIPlainField<DataType, ObjectType>>();
			newField->initSingle(name, uniqueId, getter, setter, flags);
			addNewField(newField);
		}
		
		template<class ObjectType, class DataType>
		void addReflectableField(const String& name, UINT32 uniqueId, Any getter, Any setter, UINT64 flags)
		{
			static_assert((std::is_base_of<BansheeEngine::IReflectable, DataType>::value), 
				"Invalid data type for complex field. It needs to derive from BansheeEngine::IReflectable.");

			RTTIReflectableField<DataType, ObjectType>* newField = 
				bs_new<RTTIReflectableField<DataType, ObjectType>>();
			newField->initSingle(name, uniqueId, getter, setter, flags);
			addNewField(newField);
		}

		template<class ObjectType, class DataType>
		void addReflectablePtrField(const String& name, UINT32 uniqueId, Any getter, Any setter, UINT64 flags)
		{
			static_assert((std::is_base_of<BansheeEngine::IReflectable, DataType>::value), 
				"Invalid data type for complex field. It needs to derive from BansheeEngine::IReflectable.");

			RTTIReflectablePtrField<DataType, ObjectType>* newField = 
				bs_new<RTTIReflectablePtrField<DataType, ObjectType>>();
			newField->initSingle(name, uniqueId, getter, setter, flags);
			addNewField(newField);
		}

		template<class ObjectType, class DataType>
		void addPlainArrayField(const String& name, UINT32 uniqueId, Any getter, Any getSize,
			Any setter, Any setSize, UINT64 flags)
		{
			RTTIPlainField<DataType, ObjectType>* newField = 
				bs_new<RTTIPlainField<DataType, ObjectType>>();
			newField->initArray(name, uniqueId, getter, getSize, setter, setSize, flags);
			addNewField(newField);
		}	

		template<class ObjectType, class DataType>
		void addReflectableArrayField(const String& name, UINT32 uniqueId, Any getter, Any getSize,
			Any setter, Any setSize, UINT64 flags)
		{
			static_assert((std::is_base_of<BansheeEngine::IReflectable, DataType>::value), 
				"Invalid data type for complex field. It needs to derive from BansheeEngine::IReflectable.");

			RTTIReflectableField<DataType, ObjectType>* newField = 
				bs_new<RTTIReflectableField<DataType, ObjectType>>();
			newField->initArray(name, uniqueId, getter, getSize, setter, setSize, flags);
			addNewField(newField);
		}

		template<class ObjectType, class DataType>
		void addReflectablePtrArrayField(const String& name, UINT32 uniqueId, Any getter, Any getSize,
			Any setter, Any setSize, UINT64 flags)
		{
			static_assert((std::is_base_of<BansheeEngine::IReflectable, DataType>::value), 
				"Invalid data type for complex field. It needs to derive from BansheeEngine::IReflectable.");

			RTTIReflectablePtrField<DataType, ObjectType>* newField = 
				bs_new<RTTIReflectablePtrField<DataType, ObjectType>>();
			newField->initArray(name, uniqueId, getter, getSize, setter, setSize, flags);
			addNewField(newField);
		}

		template<class ObjectType>
		void addDataBlockField(const String& name, UINT32 uniqueId, Any getter, Any setter, UINT64 flags, 
			Any customAllocator = Any())
		{
			RTTIManagedDataBlockField<ManagedDataBlock, ObjectType>* newField = 
				bs_new<RTTIManagedDataBlockField<ManagedDataBlock, ObjectType>>();
			newField->initSingle(name, uniqueId, getter,  setter, flags, customAllocator);
			addNewField(newField);
		}	
	};

	template <typename Type, typename BaseType, typename MyRTTIType>
	InitRTTIOnStart<Type, BaseType> RTTIType<Type, BaseType, MyRTTIType>::initOnStart;

	/** Returns true if the provided object can be safely cast into type T. */
	template<class T>
	bool rtti_is_of_type(IReflectable* object)
	{
		static_assert((std::is_base_of<BansheeEngine::IReflectable, T>::value), 
			"Invalid data type for type checking. It needs to derive from BansheeEngine::IReflectable.");

		return object->getTypeId() == T::getRTTIStatic()->getRTTIId();
	}

	/** Returns true if the provided object can be safely cast into type T. */
	template<class T>
	bool rtti_is_of_type(SPtr<IReflectable> object)
	{
		static_assert((std::is_base_of<BansheeEngine::IReflectable, T>::value), 
			"Invalid data type for type checking. It needs to derive from BansheeEngine::IReflectable.");

		return object->getTypeId() == T::getRTTIStatic()->getRTTIId();
	}

	/** Creates a new object just from its type ID. */
	SPtr<IReflectable> rtti_create(UINT32 rttiId);

	/** Checks is the current object a subclass of some type. */
	template<class T>
	bool rtti_is_subclass(IReflectable* object)
	{
		static_assert((std::is_base_of<BansheeEngine::IReflectable, T>::value),
			"Invalid data type for type checking. It needs to derive from BansheeEngine::IReflectable.");

		return object->isDerivedFrom(T::getRTTIStatic());
	}

	/** @} */
}