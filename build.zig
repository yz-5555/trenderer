const std = @import("std");
const zcc = @import("compile_commands");

pub fn build(b: *std.Build) !void {
    var targets = std.ArrayList(*std.Build.Step.Compile).init(b.allocator);
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const CFLAGS = .{
        // "-Wall",
        // "-Wextra",
        // "-Wcast-qual",
        // "-Wwrite-strings",
        // "-Wmissing-declarations",
        // "-Wold-style-definition",
        "-Wno-unused-parameter",
    };
    const rgb_picker = b.addExecutable(.{ .name = "rgb-picker", .optimize = optimize, .target = target });
    rgb_picker.addCSourceFile(.{
        .file = b.path("examples/rgb-picker/main.c"),
        .flags = &CFLAGS,
    });
    rgb_picker.addIncludePath(b.path(""));
    rgb_picker.linkLibC();
    b.installArtifact(rgb_picker);
    targets.append(rgb_picker) catch @panic("OOM");

    const transparent = b.addExecutable(.{ .name = "transparent", .optimize = optimize, .target = target });
    transparent.addCSourceFile(.{
        .file = b.path("examples/transparent/main.c"),
        .flags = &CFLAGS,
    });
    transparent.addIncludePath(b.path(""));
    transparent.linkLibC();
    b.installArtifact(transparent);
    targets.append(transparent) catch @panic("OOM");

    _ = zcc.createStep(b, "cdb", targets.toOwnedSlice() catch @panic("OOM"));
}
