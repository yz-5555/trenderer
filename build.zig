const std = @import("std");
const zcc = @import("compile_commands");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});
    var zcc_targets = std.ArrayListUnmanaged(*std.Build.Step.Compile){};

    const c_flags = [_][]const u8{
        "-std=c99",
        "-Wall",
        "-Wextra",
        "-Wpedantic",
        "-Wno-deprecated-declarations",
        "-Wstrict-prototypes",
    };

    const examples = [_][]const u8{ "rgb-picker", "transparent" };
    for (examples) |name| {
        const exe = b.addExecutable(.{ .name = name, .root_module = b.createModule(.{ .target = target, .optimize = optimize }) });
        exe.addCSourceFile(.{ .file = b.path(b.fmt("./examples/{s}/main.c", .{name})), .flags = &c_flags });
        exe.addCSourceFile(.{ .file = b.path("./examples/utils/key-input.c"), .flags = &c_flags });
        exe.addIncludePath(b.path("."));
        exe.addIncludePath(b.path("./examples/utils"));
        exe.linkLibC();
        b.installArtifact(exe);

        zcc_targets.append(b.allocator, exe) catch @panic("OOM");

        const run_cmd = b.addRunArtifact(exe);
        run_cmd.step.dependOn(b.getInstallStep());

        const run_step = b.step(b.fmt("run-{s}", .{name}), "Running the example");
        run_step.dependOn(&run_cmd.step);
    }
    _ = zcc.createStep(b, "cdb", zcc_targets.toOwnedSlice(b.allocator) catch @panic("OOM"));
}
