#pragma once

#define ROLLSCRIPT_ERROR(userMessage, technicalMessage) \
setErrorInternal(                                  \
                                                   userMessage,                                   \
                                                   technicalMessage,                              \
                                                   __FILE__,                                      \
                                                   Q_FUNC_INFO,                                   \
                                                   __LINE__)


#define ROLLSCRIPT_ERROR_CAUSE(userMessage, technicalMessage, cause) \
    setErrorInternal(                                               \
                                                                    userMessage,                                                \
                                                                    technicalMessage,                                           \
                                                                    __FILE__,                                                   \
                                                                    Q_FUNC_INFO,                                                \
                                                                    __LINE__,                                                   \
                                                                    cause)

