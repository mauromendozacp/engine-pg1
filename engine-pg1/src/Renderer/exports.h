#ifndef EXPORTS_H
#define EXPORTS_H

#ifdef GRAPHICSENGINE_EXPORTS
#define GRAPHICSENGINE_API __dedeclspec(dllexport)
#else
#define GRAPHICSENGINE_API __dedeclspec(dllexport)
#endif // GRAPHICSENGINE_EXPORTS

#endif // !EXPORTS_H