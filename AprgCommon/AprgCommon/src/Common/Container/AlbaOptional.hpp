#pragma once

#include <cassert>
#include <memory>
#include <ostream>

namespace alba {

template <typename ContentType>
// class [[deprecated("Use std::optional instead! (needs c++17)")]]
class AlbaOptional {
    // This requires copy constructor and default constructor on ContentType
public:
    AlbaOptional() = default;
    explicit AlbaOptional(ContentType const content) : m_contentPointer(std::make_unique<ContentType>(content)) {}
    explicit AlbaOptional(ContentType& content) : m_contentPointer(std::make_unique<ContentType>(content)) {}
    ~AlbaOptional() = default;

    AlbaOptional(AlbaOptional const& optional) {
        if (optional.m_contentPointer) {
            m_contentPointer = std::make_unique<ContentType>(*(optional.m_contentPointer));
        }
    }

    AlbaOptional(AlbaOptional&& optional) noexcept : m_contentPointer(std::move(optional.m_contentPointer)) {}

    AlbaOptional& operator=(AlbaOptional const& optional) {
        if (this == &optional) {
            return *this;
        }
        if (optional.m_contentPointer) {
            m_contentPointer = std::make_unique<ContentType>(*(optional.m_contentPointer));
        }
        return *this;
    }

    AlbaOptional& operator=(AlbaOptional&& optional) noexcept {
        m_contentPointer = std::move(optional.m_contentPointer);
        return *this;
    }

    explicit operator bool() const { return hasContent(); }
    explicit operator ContentType() const { return get(); }

    [[nodiscard]] ContentType get() const {
        assert(m_contentPointer);  // not allowing any mistakes
        if (m_contentPointer) {
            return *(m_contentPointer);
        }
        return ContentType();
    }

    [[nodiscard]] ContentType const& getConstReference() const {
        assert(m_contentPointer);  // not allowing any mistakes
        return *(m_contentPointer);
    }

    [[nodiscard]] bool hasContent() const { return static_cast<bool>(m_contentPointer); }
    void createObjectUsingDefaultConstructor() { m_contentPointer = std::make_unique<ContentType>(); }

    void setValue(ContentType const content) {
        if (m_contentPointer) {
            *m_contentPointer = content;
        } else {
            m_contentPointer = std::make_unique<ContentType>(content);
        }
    }

    void setConstReference(ContentType const& content) {
        if (m_contentPointer) {
            *m_contentPointer = content;
        } else {
            m_contentPointer = std::make_unique<ContentType>(content);
        }
    }

    void clear() { m_contentPointer.reset(); }

    ContentType& getReference() {
        assert(m_contentPointer);  // not allowing any mistakes
        return *(m_contentPointer);
    }

private:
    friend std::ostream& operator<<(std::ostream& out, AlbaOptional const& optional) {
        out << "hasContent: " << optional.hasContent();
        if (optional.hasContent()) {
            out << " value: " << optional.getConstReference();
        }
        return out;
    }

    std::unique_ptr<ContentType> m_contentPointer;
};

template <typename ContentType>
// class [[deprecated("Check if std::reference_wrapper can be used instead.")]] AlbaOptional
// lets remove [[deprecated]] to avoid unnecessary warnings
class AlbaOptional<ContentType&> {
public:
    // #warning Please make sure that object still exists in the life time of an optional reference object
    AlbaOptional() = default;
    // std::addressof should be used because & might be overloaded
    explicit AlbaOptional(ContentType& content) : m_hasContent(true), m_contentPointer(std::addressof(content)) {}
    ~AlbaOptional() = default;

    AlbaOptional(AlbaOptional const& optional)
        : m_hasContent(optional.m_hasContent), m_contentPointer(optional.m_contentPointer) {}

    AlbaOptional(AlbaOptional&& optional) noexcept = delete;

    AlbaOptional& operator=(AlbaOptional const& optional) {
        if (this != &optional) {
            m_hasContent = optional.m_hasContent;
            m_contentPointer = optional.m_contentPointer;
        }
        return *this;
    }

    AlbaOptional& operator=(AlbaOptional&& optional) noexcept = delete;
    explicit operator bool() const { return m_hasContent; }

    explicit operator ContentType&() const {
        if (m_hasContent && isContentPointerValid()) {
            return *m_contentPointer;
        }
        return m_empty;
    }

    [[nodiscard]] ContentType& get() const {
        if (m_hasContent && isContentPointerValid()) {
            return *m_contentPointer;
        }
        return m_empty;
    }

    [[nodiscard]] bool hasContent() const { return m_hasContent; }

    void setValue(ContentType const content) {
        if (m_hasContent && isContentPointerValid()) {
            *m_contentPointer = content;
        }
    }

    void setReference(ContentType& content) {
        m_hasContent = true;
        m_contentPointer = std::addressof(content);
    }

    void clear() {
        m_hasContent = false;
        m_contentPointer = nullptr;
    }

private:
    [[nodiscard]] inline bool isContentPointerValid() const { return m_contentPointer != nullptr; }

    friend std::ostream& operator<<(std::ostream& out, AlbaOptional const& optional) {
        out << "hasContent: " << optional.m_hasContent;
        if (optional.m_hasContent) {
            out << " value: " << optional.get();
        }
        return out;
    }

    bool m_hasContent{false};
    ContentType* m_contentPointer{nullptr};
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static ContentType m_empty;  // think of how to remove this
};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
template <typename ContentType>
ContentType AlbaOptional<ContentType&>::m_empty{};

}  // namespace alba
