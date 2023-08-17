/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 Main AaGpuXmlParser API header file
* @module                AaGpuXmlParser
* @owner                 Marcela Nemet
*
* Copyright 2014 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_AAGPUXMLPARSER_HPP
#define _MCU_RT_AAGPUXMLPARSER_HPP
#include "CcsCommon.h"

/************************** DOXYGEN GROUPS ************************************/

/**
 *  @defgroup dgAaGpuXml      Gpu Xml Parser (AaGpuXml)
 *  @ingroup  dgBasicSystemSw
 *
 *  Common Computer and Support SW System Gpu Xml Parser Service.
 *
 *  @par        Configuring Service
 *
 */

/**
 *  @defgroup dgAaGpuXmlApi API
 *  @ingroup  dgAaGpuXml
 *
 *  Application Programming Interface.
 */
/*@{*/

#ifdef WIN32
    #pragma once
    #pragma warning(disable: 4290)
#endif

// include files
#include <string>
#include <algorithm>
#include <glo_def.h>

#include <list>


class AaGpuXmlNode;
typedef std::list<AaGpuXmlNode*>::const_iterator TAaGpuXmlNodeListConstIterator;

typedef enum {
    AA_GPU_XML_DATA_ILL_FORMED     = 1, /* XML document or XML validation data was syntactically incorrect */
    AA_GPU_XML_DATA_INVALID        = 2, /* XML document did not match the specified validation document */
    AA_GPU_XML_DATA_WELL_FORMED    = 3, /* XML document was syntactically correct */
    AA_GPU_XML_DATA_VALID          = 4, /* XML document was succesfully validated against the specified validation document */
    AA_GPU_XML_DATA_NOT_SET        = 5, /* Called some of the parse methods without setting the XML document data */
    AA_GPU_XML_UNKNOWN_ERROR       = 6  /* Unknown error occured during parsing */
} EAaGpuXmlParsingResult;

typedef enum {
    AA_GPU_XML_INVALID        = 0,
    AA_GPU_XML_ELEMENT_NODE   = 1,
    AA_GPU_XML_ATTRIBUTE_NODE = 2,
    AA_GPU_XML_ROOT_NODE      = 3
} EAaGpuXmlNodeType;


/**
 * @defgroup dgAaGpuXmlApiMcu AaGpuXml MCU API
 * @ingroup  dgAaGpuXml
 */

/* @{ */

/**
 * @brief Singleton class, will be automatically destroyed when the system shutdown.
 */
class AaGpuXmlInit
{
public:
   /**
    * @brief Destructor.
    */
    ~AaGpuXmlInit();

   /**
    * @brief Initialization not used.
    *
    * @return GLO_TRUE constant because initialization not used
    */
    TBoolean AaGpuXmlInitialize(void);

private:
   /**
    * @brief Constructor. Initially empty method.
    */
    AaGpuXmlInit() ;

   /**
    * @brief Copy constructor. NOT IMPLEMENTED!
    */
    AaGpuXmlInit(const AaGpuXmlInit&);

   /**
    * @brief Assignment operator. NOT IMPLEMENTED!
    */
    AaGpuXmlInit& operator=(const AaGpuXmlInit&);

public:

    static AaGpuXmlInit* m_instance;

   /**
    * @brief Create instance of the class if not created and return
    *        pointer to it. Instance is saved to the m_instance.
    *
    * @return Instance of the AaGpuXmlInit class.
    */
    static AaGpuXmlInit* AaGpuXmlGetInstance(void);
};

/**
 * @brief Offers basic methods to investigate nodes and browse through the tree
 */
class AaGpuXmlNode
{
    friend class AaGpuXmlParser;
    typedef std::list<AaGpuXmlNode*> AaGpuXmlNodeList;
    typedef std::list<AaGpuXmlNode*>::iterator AaGpuXmlNodeListIterator;
public:

   /**
    * @brief Constructor
    */
    AaGpuXmlNode() ;

   /**
    * @brief Destructor. Free all allocated memory.
    */
    ~AaGpuXmlNode() ;

   /**
    * @brief AaGpuXmlDump every node tag and value to the output
    *     stream if AaGpuXmlParser prints is enabled using RD switch
    */
    void AaGpuXmlDump(void) const;

   /**
    * @brief Construct XML document from the nodes in the tree and
    *         return document as std::string. If this method is
    *         called for any other node than root then the returned
    *         string is empty. Uses method string
    *         AaGpuXmlNode::dumpXml(i32 steppingLevel) to retrieve child
    *         nodes information.
    *
    * @return Formatted XML document
    */
    std::string AaGpuXmlDumpXml(void) const ;

   /**
    * @brief Calculates every node combined size in bytes.
    *
    * @return Combined size of every node name, value and size
    *         in the tree.
    */
    u32 AaGpuXmlGetSize(void) const;

   /**
    * @brief To check has node any childrens
    *        Return GLO_TRUE if node has one or more childrens.
    *
    * @return GLO_TRUE = has children
    *         GLO_FALSE = no children
    */
    TBoolean AaGpuXmlHasChildren(void) ;

   /**
    * @brief Return type of the node.
    *
    * @return Type of the node. See file EAaGpuXmlNodeType.h.
    */
    EAaGpuXmlNodeType AaGpuXmlGetType(void) const ;

    // to get a name and value
   /**
    * @brief Return tag name of the node.
    *
    * @return Tag name
    */
    std::string AaGpuXmlGetName(void) const ;

   /**
    * @brief Return value of the node.
    *
    * @return Value of the node.
    */
    std::string AaGpuXmlGetValue(void) const ;

   /**
    * @brief Method to retrieve previous node in the tree.
    *
    * @return Pointer to previous node.
    */
    AaGpuXmlNode* AaGpuXmlGetPrev(void) const ;

   /**
    * @brief Return pointer to next node in the tree.
    *
    * @return Pointer to next node or GLO_NULL if current node is last node in the tree.
    */
    AaGpuXmlNode* AaGpuXmlGetNext(void) const ;

   /**
    * @brief Return parent node.
    *
    * @return Pointer to parent node or GLO_NULL if current node is root node.
    */
    AaGpuXmlNode* AaGpuXmlGetParent(void) const ;

   /**
    * @brief Return iterator to first children of current node.
    *
    * @return Iterator to children. See file TAaGpuXmlNodeListConstIterator.h
    */
    TAaGpuXmlNodeListConstIterator AaGpuXmlGetFirstChildren(void) const ;

   /**
    * @brief Return iterator to last children of current node.
    *
    * @return Iterator to children. See file TAaGpuXmlNodeListConstIterator.h
    */
    TAaGpuXmlNodeListConstIterator AaGpuXmlGetLastChildren(void) const ;

    // to set node information
   /***
    * @brief Set type of the node.
    *
    * @param[in] type  Type of the node. See file EAaGpuXmlNodeType.h for valid types.
    */
    void AaGpuXmlSetType(const EAaGpuXmlNodeType type) ;

   /**
    * @brief Set tag name of the node.
    *
    * @param[in] name tag name.
    */
    void AaGpuXmlSetName(const std::string& name) ;

   /**
    * @brief Set value of the node.
    *
    * @param[in] value a node value.
    */
    void AaGpuXmlSetValue(const std::string& value) ;

private:
    // helpers
   /**
    * @brief Set previous node.
    *
    * @param[in] node pointer to previous node.
    */
    void AaGpuXmlSetPrev(AaGpuXmlNode* node) ;

   /**
    * @brief Set next node.
    *
    * @param[in] node pointer to next node.
    */
    void AaGpuXmlSetNext(AaGpuXmlNode* node) ;

   /**
    * @brief Set parent of the node.
    *
    * @param[in] node pointer to parent node.
    * @sa
    *     - _AaGpuXmlSetParent(AaGpuXmlNode* node)
    *     - __AaGpuXmlSetParent(AaGpuXmlNode* node)
    */
    void AaGpuXmlSetParent(AaGpuXmlNode* node) ;

   /**
    * @brief Add children to the list of childrens.
    *
    * @param[in] node pointer to children to add.
    * @sa
    *     - _AaGpuXmlAddChildren(AaGpuXmlNode* node)
    */
    void AaGpuXmlAddChildren(AaGpuXmlNode* node) ;

   /**
    * @brief Remove children from the list of childrens.
    *
    * @param[in] node pointer to children to remove.
    * @sa
    *     - _AaGpuXmlRemoveChildren(AaGpuXmlNode* node)
    */
    void AaGpuXmlRemoveChildren(AaGpuXmlNode* node) ;

   /**
    * @brief Remove all children by clearing a list of children.
    */
    void AaGpuXmlClearChildren(void) ;

   /**
    * @brief Helper to set parent node. Parent setting is divided
    *        to three parts. This method is the third of them.
    *        Just set parent to given node.
    *
    * @param[in] node pointer to parent node.
    * @sa
    *     - AaGpuXmlSetParent(AaGpuXmlNode* node)
    *     - _AaGpuXmlSetParent(AaGpuXmlNode* node)
    */
    void __AaGpuXmlSetParent(AaGpuXmlNode* node) ;

   /**
    * @brief Another helper to set parent. Parent setting is divided
    *        to three parts. This method is the second of them
    *
    * @param[in] node pointer to parent node.
    * @sa
    *     - AaGpuXmlSetParent(AaGpuXmlNode* node)
    *     - __AaGpuXmlSetParent(AaGpuXmlNode* node)
    */
    void _AaGpuXmlSetParent(AaGpuXmlNode* node) ;

   /**
    * @brief Reset parent of the node.
    */
    void _AaGpuXmlClearParent(void) ;

   /**
    * @brief Helper to add children to the list of childrens.
    *        Children adding is divided to two parts.
    *        This is the second of them.
    *
    * @param[in] node pointer to children to add.
    * @sa
    *     - AaGpuXmlAddChildren(AaGpuXmlNode* node)
    */
    void _AaGpuXmlAddChildren(AaGpuXmlNode* node) ;

   /**
    * @brief Helper to remove children. Children remove is divided
    *        to two parts. This method is the second of them.
    *
    * @param[in] node pointer to children to remove.
    * @sa
    *     - AaGpuXmlRemoveChildren(AaGpuXmlNode* node)
    */
    void _AaGpuXmlRemoveChildren(AaGpuXmlNode* node) ;

   /**
    * @brief Cleanup relations between nodes.
    */
    void AaGpuXmlCleanUpRelations(void) ;

   /**
    * @brief Helper to retrieve child nodes information.
    *
    * @param[in] steppingLevel
    * @return Formatted XML document containing child nodes information
    */
    std::string AaGpuXmlDumpXml(i32 steppingLevel) const ;

private:
    // hidden methods (not implemented)
    AaGpuXmlNode(const AaGpuXmlNode& copy) ;
    AaGpuXmlNode& operator=(const AaGpuXmlNode& copy) ;

private:

    EAaGpuXmlNodeType m_type;    //!< type of the node

    std::string m_name;          //!< a name of the tag

    std::string m_value;         //!< a value of the tag if any

    AaGpuXmlNode* m_prev;        //!< previous node

    AaGpuXmlNode* m_next;        //!< next node

    AaGpuXmlNode* m_parent;      //!< parent node

    AaGpuXmlNodeList m_children; //!< child nodes

    i16 m_depth;            //!< level in a tree. Used for building relationships
};

/**
 * @brief Class used for description of parsing object.
 */
class AaGpuXmlParser
{

public:
    // constructors / destructor
    /**
    * @brief Default constructor. Initialize XML data and
    *      XML validation data members with given parameters.
    *
    * @param[in] exitOnFirstFatalError flag for exceptions (!!! NOT USED !!!).
    */
    AaGpuXmlParser(const TBoolean exitOnFirstFatalError = GLO_FALSE);

   /**
    * @brief Parameter constructor. Initialize XML data and
    *      XML validation data members with given parameters.
    *
    * @param[in] xmlData string containing XML document.
    * @param[in] xmlValidation string containing validation data (!!! NOT USED !!!).
    * @param[in] exitOnFirstFatalError flag for exceptions (!!! NOT USED !!!).
    */
    AaGpuXmlParser(const std::string& xmlData, const std::string& xmlValidation, const TBoolean exitOnFirstFatalError = GLO_FALSE) ;

   /**
    * @brief Destructor. Delete m_names list items if exists.
    */
    virtual ~AaGpuXmlParser() ;

    // parsing methods
   /**
    * @brief Method to do actual parsing
    *
    * @return
	*     AaGpuXmlNode root node of the AaGpuXmlNode tree or GLO_NULL if error.
    * @sa
    *     - AaGpuXmlParse(AaGpuXmlNode* parentNode),
    *     - AaGpuXmlParse(const std::string& xmlData, const std::string& xmlValidationData),
    *     - AaGpuXmlParse(const std::string& xmlData),
    *     - AaGpuXmlSetXmlData(const std::string& xmlData)
    *
    * Called from methods:
    *     - AaGpuXmlParse(const std::string& xmlData, const std::string& xmlValidationData)
    *     - AaGpuXmlParse(const std::string& xmlData)
    */
    AaGpuXmlNode* AaGpuXmlParse(void) ;

   /**
    * @brief Overloaded method to parse XML document. Initialize
    *     data members and call method AaGpuParse(void) to do actual parsing.
    *
    * @param[in] xmlData string containing XML document.
    * @param[in] xmlValidation string containing validation data (!!! NOT USED !!!).
    * @return AaGpuXmlNode root node of the AaGpuXmlNode tree or GLO_NULL if error.
    * @sa
    *     - AaGpuXmlParse(AaGpuXmlNode* parentNode),
    *     - AaGpuXmlParse(void),
    *     - AaGpuXmlParse(const std::string& xmlData),
    *     - AaGpuXmlSetXmlData(const std::string& xmlData)
    */
    AaGpuXmlNode* AaGpuXmlParse(const std::string& xmlData, const std::string& xmlValidation) ;

   /**
    * @brief Overloaded method to parse XML document. Initialize
    *     data members and call method AaGpuParse(void) to do actual parsing.
    *
    * @param[in] xmlData string containing XML document.
    * @return AaGpuXmlNode root node of the AaGpuXmlNode tree or GLO_NULL if error.
    * @sa
    *     - AaGpuXmlParse(AaGpuXmlNode* parentNode),
    *     - AaGpuXmlParse(const std::string& xmlData, const std::string& xmlValidationData),
    *     - AaGpuXmlParse(void),
    *     - AaGpuXmlSetXmlData(const std::string& xmlData)
    */
    AaGpuXmlNode* AaGpuXmlParse(const std::string& xmlData) ;

   /**
    * @brief Set m_xmlData member to given string.
    *
    * @param[in] xmlData string containing XML document.
    */
    void AaGpuXmlSetXmlData(const std::string& xmlData) ;

   /**
    * @brief Empty method because validation is not in use
    *
    * @param[in] xmlValidationData string containing validation data (!!! NOT USED !!!).
    */
    void AaGpuXmlSetXmlValidationData(const std::string& xmlValidationData);

    // configuration

   /**
    * @brief Empty method because exceptions are not in use
    *
    * @param[in] exitOnFirstFatalError
    *     - GLO_TRUE = Parse without exceptions.
    *     - GLO_FALSE = Parse without exceptions.
    *     - Default value is GLO_FALSE.
    */
    void AaGpuXmlSetExitOnFirstFatalError(const TBoolean exitOnFirstFatalError) ;

   /**
    * @brief Return GLO_FALSE because exceptions are not in use
    *
    * @return GLO_FALSE
    */
    TBoolean AaGpuXmlGetExitOnFirstFatalError(void) const ;

   /**
    * @brief Set m_lastResult member to given EAaGpuXmlParsingResult -type value
    *
    * @param[in] result
    *               - 1 = AA_GPU_XML_DATA_ILL_FORMED.
    *               - 3 = AA_GPU_XML_DATA_WELL_FORMED.
    *               - 5 = AA_GPU_XML_DATA_NOT_SET.
    */
    void AaGpuXmlSetLastResult(const EAaGpuXmlParsingResult result);

   /**
    * @brief To check last parsing result. Another way to check
    *     that parsing was success
    *
    * @return 1 = AA_GPU_XML_DATA_ILL_FORMED.
    *         3 = AA_GPU_XML_DATA_WELL_FORMED.
    *         5 = AA_GPU_XML_DATA_NOT_SET.
    * @sa AaGpuXmlsucceeded()
    */
    EAaGpuXmlParsingResult AaGpuXmlGetLastResult(void) const;

    // status methods

   /**
    * @brief Method to reset errors. Just set member m_lastResult
    *     to AA_GPU_XML_DATA_WELL_FORMED
    */
    void AaGpuXmlResetErrors(void) ;

   /**
    * @brief To check was last parsing success.
    *
    * @return GLO_TRUE = last parsing was success.
    *         GLO_FALSE = last parsing fail.
    * @sa AaGpuXmlGetLastResult()
    */
    TBoolean AaGpuXmlSucceeded(void) const ;

private:

   /**
    * @brief Method to do actual XML document parsing after root node.
    *
    * @param[in] parentNode Parent node whom child will be set
    *
    * Called from methods:
    *     - AaGpuXmlParse(void)
    */
    void AaGpuXmlParse(AaGpuXmlNode* parentNode);

    // helpers
   /**
    * @brief Remove leading and trailing whitespace from given string.
    *
    * @param[in] str string to trim.
    */
    void AaGpuXmlTrimString(std::string& str) ;

   /**
    * @brief Remove XML -header from m_xmlData string member.
    *
    * Called from methods:
    *     - AaGpuXmlParse(void)
    */
    void AaGpuXmlSkipXmlHeader(void);

   /**
  * @brief Remove comment -headers from m_xmlData string member.
  *
  * Called from methods:
  *     - AaGpuXmlParse(void)
  *     - AaGpuXmlParse(AaGpuXmlNode* parentNode)
  *     - AaGpuXmlSkipEndNodes(void)
  */
  void AaGpuXmlSkipCommentHeaders(void);

   /**
    * @brief Set node members: m_name, m_value, attributes and
    *     relationships to other nodes.
    *
    * @param[in] node node to set.
    *
    * Called from methods:
    *     - AaGpuXmlParse(void)
    *     - AaGpuXmlParse(AaGpuXmlNode* parentNode)
    */
    void AaGpuXmlSetNode(AaGpuXmlNode* node);

   /**
    * @brief Read nodename from m_xmlData string -type member.
    *
    * @param[in] name Reference to node name
    *
    * Called from methods:
    *     - AaGpuXmlSetNode(AaGpuXmlNode* node)
    */
    void AaGpuXmlReadName(std::string& name);

   /**
    * @brief Read value of node from m_xmlData string -type member.
    *
    * @param[in] value Reference to node value
    *
    * Called from methods:
    *     - AaGpuXmlSetNode(AaGpuXmlNode* node)
    */
    void AaGpuXmlReadValue(std::string& value);

   /**
    * @brief Read value of attribute from m_xmlData member.
    *
    * @param[in] value Reference to value of attribute
    *
    * Called from methods:
    *     - AaGpuXmlSetAttribute(AaGpuXmlNode* node)
    */
    void AaGpuXmlReadAttributeValue(std::string & value);

   /**
    * @brief Method to set name, value and relationships for attribute.
    *
    * @param[in] node Parent node whom attributes will be set
    *
    * Called from methods:
    *     - AaGpuXmlSetNode(AaGpuXmlNode* node)
    */
    void AaGpuXmlSetAttribute(AaGpuXmlNode* node);

   /**
    * @brief Method to Build child, parent and sibling
    *     relationships for node.
    *
    * @param[in] node Node whom relationships will be build.
    *
    * Called from methods:
    *     - AaGpuXmlSetNode(AaGpuXmlNode* node)
    */
    void AaGpuXmlBuildRelationship(AaGpuXmlNode* node);

   /**
    * @brief Remove end nodes from m_xmlData member.
    *
    * Called from methods:
    *     - AaGpuXmlParse(AaGpuXmlNode* parentNode)
    */
    void AaGpuXmlSkipEndNodes(void);

   /**
    * @brief Replace entities with real characters.
    *
    * @param[in] text Reference to string including entities.
    *
    * Called from method:
    *     - AaGpXmluParse()
    */
    void AaGpuXmlGetEntity(std::string &text);

   /**
    * @brief Copy aCount number of charactes from
    *		 aSource to aDestination.
    *
    * @param[in] aDestination Reference to destination string
    * @param[in] aSource Pointer to source of charactes
    * @param[in] aCount Amount of charactes
    *
    * Called from method:
    *     - AaGpuXmlReadName()
    *     - AaGpuXmlReadValue()
    *     - AaGpuXmlSetAttribute()
    *     - AaGpuXmlSkipEndNodes()
    *     - AaGpuXmlGetEntity()
    */
    inline void AaGpuXmlCpyToStrnEntity(std::string& aDestination, const char* aSource, u32 aCount);

private:
    // hidden methods (not implemented)
    AaGpuXmlParser(const AaGpuXmlParser& copy) ;
    AaGpuXmlParser& operator=(const AaGpuXmlParser& copy) ;

   /**
    * @brief Entity and corresponding character struct
    */
    struct Entity
    {
        const char* str;      //!< Entity
        char        chr;      //!< Corresponding char
    };
    enum
    {
        NUM_ENTITY = 11
    };
    static Entity entity[ NUM_ENTITY ]; //!< chars for replacing entities.

private:

    std::string m_xmlData;   //!< member for XML document
    EAaGpuXmlParsingResult m_lastResult;
    i32 m_location;   //!< location of processing in m_xmlData
    i16 m_depth;       //!< level in a tree. Used for building relationships
    std::list<char*> m_names;  //!< list for checking a corresponding start and end tags
};

/*@}*/

/*@}*/

#endif /* _MCU_RT_AAGPUXMLPARSER_HPP */
